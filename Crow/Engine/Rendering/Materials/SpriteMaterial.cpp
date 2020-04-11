//
// Created by Igli milaqi on 05/04/2020.
//

#include "SpriteMaterial.h"

#include "../../Rendering/Shader.h"
#include "../../Components/SpriteInfo.h"
#include "../../Core/Game.h"
#include "../../Core/ResourceManager.h"

SpriteMaterial::SpriteMaterial() : AbstractMaterial("spriteShader")
{
    Initialize();
}

void SpriteMaterial::Initialize()
{
    //TODO make screen size a global value and not hardcode it!
    m_orthoProjection = glm::ortho(0.0f, static_cast<GLfloat>(1920),
                                   static_cast<GLfloat>(1080), 0.0f, -1.0f, 1.0f);

    m_shader->SetInt("image",0);
    m_uProjection = m_shader->GetUniformLocation("projection");
    m_uSpriteColor = m_shader->GetUniformLocation("spriteColor");
}

void SpriteMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    
    glUniform3fv(m_uSpriteColor, 1, glm::value_ptr(color));
}

void SpriteMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                          const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    m_shader->Use();

    glUniformMatrix4fv(m_uProjection, 1, GL_FALSE, glm::value_ptr(m_orthoProjection));
}
