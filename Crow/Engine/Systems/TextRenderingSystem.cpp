//
// Created by Igli milaqi on 03/04/2020.
//

#include "../Core/Game.h"
#include "TextRenderingSystem.h"
#include "../Rendering/Font.h"
#include "../Core/ResourceManager.h"
#include "../Components/Text.h"
#include "../Components/Transform.h"
#include "../Rendering/Shader.h"

void TextRenderingSystem::Init()
{
    System::Init();

    m_shader = Game::Instance()->resourceManager->GetShader("textShader");

    BufferAllTextComponents();
}

void TextRenderingSystem::Render()
{
    System::Render();

    auto entities = world->EntitiesWith<Transform,Text>();

    for (int i = 0; i < entities.size() ; ++i)
    {
        Text& text = world->GetComponent<Text>(entities[i]);
        Transform& textTransform = world->GetComponent<Transform>(entities[i]);
        RenderText(&text,textTransform.WorldPosition().x,textTransform.WorldPosition().y);
    }
}

void TextRenderingSystem::BufferAllTextComponents()
{
    const std::map<std::string,Font*>& fontMap = Game::Instance()->resourceManager->InternalGetFontMap();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(1920), 0.0f, static_cast<GLfloat>(1080));
    m_shader->Use();
    glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


    for (const auto& fontPair : fontMap)
    {
        Font* font = fontPair.second;
        FT_Face face = *font->m_fontFace;

        //Go through all the ASCII characters and buffer them and in the end store them in the map
        for (GLubyte c = 0; c < 128; c++)
        {

            if (FT_Load_Char(face,c,FT_LOAD_RENDER))
            {
               ENGINE_LOG_ERROR("FREETYTPE: Failed to load Glyph");
               continue;
            }

            GLuint texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
            );
            // Set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // Now store character for later use
            Character character = {
                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    texture,
                    (GLuint)face->glyph->advance.x
            };

            font->m_charactersMap.insert(std::pair<GLchar, Character>(c, character));
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        }
    }

    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderingSystem::RenderText(Text* text,float x,float y)
{
    m_shader->Use();

    glUniform3f(glGetUniformLocation(m_shader->ID, "textColor"), text->color.x, text->color.y, text->color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    // Iterate through all characters
    std::string::const_iterator c;
    for (c = text->textString.begin(); c != text->textString.end(); c++)
    {
        Character ch = text->font->m_charactersMap[*c];

        GLfloat xpos = x + ch.bearing.x * text->scale;
        GLfloat ypos = y - (ch.size.y - ch.bearing.y) * text->scale;

        GLfloat w = ch.size.x * text->scale;
        GLfloat h = ch.size.y * text->scale;
        // Update VBO for each character
        GLfloat vertices[6][4] = {
                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos,     ypos,       0.0, 1.0 },
                { xpos + w, ypos,       1.0, 1.0 },

                { xpos,     ypos + h,   0.0, 0.0 },
                { xpos + w, ypos,       1.0, 1.0 },
                { xpos + w, ypos + h,   1.0, 0.0 }
        };

        glBindTexture(GL_TEXTURE_2D, ch.textureID);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * text->scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

