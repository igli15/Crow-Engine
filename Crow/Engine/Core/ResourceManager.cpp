//
// Created by Igli milaqi on 07/03/2020.
//

#include "ResourceManager.h"
#include "../../Plugins/stb_image.h"
#include "../../Crow.h"

#include "../Rendering/Font.h"
#include "../Rendering/Sprite.h"


Texture *ResourceManager::LoadTexture(const std::string &path, const std::string &name)
{

    auto iterator = m_textures.find(name);

    if(iterator != m_textures.end())
    {
        ENGINE_LOG_ERROR("There is already a texture with name: " + name);
        throw;
    }

    Texture *texture = new Texture();
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load((TEXTURE_PATH + path).data(), &width, &height, &nrChannels, 0);

    if (!data)
    {
        ENGINE_LOG_ERROR("There is no texture in path: " + path);
    }

    texture->data = data;
    texture->width = width;
    texture->height = height;
    texture->nrOfChannels = nrChannels;

    texture->Generate(width,height,data);

    m_textures[name] = texture;

    return texture;
}

Shader* ResourceManager::CreateShader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &name)
{
    auto iterator = m_shaders.find(name);

    if(iterator != m_shaders.end())
    {
        ENGINE_LOG_CRITICAL("There is already a shader with name: " + name);
        throw;
    }

    Shader * shader = new Shader(SHADER_PATH + vertexPath, SHADER_PATH + fragmentPath);
    m_shaders[name] = shader;

    Game::Instance()->renderer->allShaders.push_back(shader);

    return shader;
}

Texture *ResourceManager::GetTexture(const std::string &name)
{
    auto iterator = m_textures.find(name);

    if (iterator == m_textures.end())
    {
        ENGINE_LOG_ERROR("There is no Texture with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

Shader *ResourceManager::GetShader(const std::string &name)
{
    auto iterator = m_shaders.find(name);

    if (iterator == m_shaders.end())
    {
        ENGINE_LOG_ERROR("There is no Shader with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

Model *ResourceManager::LoadModel(const std::string &path, const std::string &name)
{
    Model *model = new Model((MODEL_PATH + path).data());

    auto iterator = m_models.find(name);

    if (iterator != m_models.end())
    {
        ENGINE_LOG_ERROR("There is already a model with name: " + name);
        throw;
    }
    else
    {
        m_modelIdCounter++;
        model->ID = m_modelIdCounter;
        m_models.insert(iterator,std::make_pair(name,model));
        return model;
    }

    return nullptr;
}

Model *ResourceManager::GetModel(const std::string &name) {

    auto iterator = m_models.find(name);

    if (iterator == m_models.end())
    {
        ENGINE_LOG_ERROR("There is no Model with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

Font *ResourceManager::LoadFont(const std::string &path, const std::string &name)
{
    auto iterator = m_fonts.find(name);

    if (iterator != m_fonts.end())
    {
        ENGINE_LOG_ERROR("There is already a font with name: " + name);
        throw;
    }

    Font *font = new Font(FONT_PATH + path, 48);

    m_fonts[name] = font;

    return font;
}

Font *ResourceManager::GetFont(const std::string &name) {

    auto iterator = m_fonts.find(name);
    if (iterator == m_fonts.end())
    {
        ENGINE_LOG_ERROR("There is no Font with name: " + name);
        return nullptr;
    }

    return iterator->second;
}

const std::map<std::string, Font *> &ResourceManager::InternalGetFontMap()
{
    return m_fonts;
}

Sprite *ResourceManager::CreateSprite(const std::string &name, Texture *texture)
{
    auto iterator = m_sprites.find(name);

    if (iterator != m_sprites.end())
    {
        ENGINE_LOG_ERROR("There is already a sprite with name: " + name);
        throw;
    }

    Sprite* sprite = new Sprite();

    sprite->texture = texture;
    m_spriteIdCounter++;
    sprite->ID = m_spriteIdCounter;
    m_sprites[name] = sprite;

    return sprite;
}

Sprite *ResourceManager::GetSprite(const std::string &name)
{
    auto iterator = m_sprites.find(name);

    if (iterator == m_sprites.end())
    {
        ENGINE_LOG_ERROR("There is no sprite with name: " + name);
        return nullptr;
    }

    return iterator->second;
}
