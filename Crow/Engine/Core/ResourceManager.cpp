//
// Created by Igli milaqi on 07/03/2020.
//

#include "ResourceManager.h"
#include "../../Plugins/stb_image.h"
#include "../../Crow.h"

#include "../Rendering/Font.h"
#include "../Rendering/Sprite.h"


Texture *ResourceManager::LoadTexture(const std::string &path, const std::string &name) {
    Texture *texture = new Texture();
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(false);
    unsigned char *data = stbi_load((path).data(), &width, &height, &nrChannels, 0);

    if (!data) {
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
        ENGINE_LOG_CRITICAL("Shader with that name is already created!");
        throw;
    }

    Shader * shader = new Shader(vertexPath, fragmentPath);
    m_shaders[name] = shader;

    Game::Instance()->renderer->allShaders.push_back(shader);

    return shader;
}

Texture *ResourceManager::GetTexture(const std::string &name) {

    if (m_textures.find(name) == m_textures.end()) {
        ENGINE_LOG_ERROR("There is no Texture with that name!");
    }

    return m_textures[name];
}

Shader *ResourceManager::GetShader(const std::string &name) {
    if (m_shaders.find(name) == m_shaders.end()) {
        ENGINE_LOG_ERROR("There is no Shader with that name!");
    }

    return m_shaders[name];
}

Model *ResourceManager::LoadModel(const std::string &path, const std::string &name) {
    Model *model = new Model(path.data());

    auto iterator = m_models.find(name);

    if (iterator != m_models.end())
    {
        ENGINE_LOG_CRITICAL("Model with that name already exists!");
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
    if (m_models.find(name) == m_models.end()) {
        ENGINE_LOG_ERROR("There is no Model with that name!");
    }

    return m_models[name];
}

Font *ResourceManager::LoadFont(const std::string &path, const std::string &name) {
    Font *font = new Font(path, 48);

    m_fonts[name] = font;

    return font;
}

Font *ResourceManager::GetFont(const std::string &name) {
    if (m_fonts.find(name) == m_fonts.end()) {
        ENGINE_LOG_ERROR("There is no Font with that name!");
    }

    return m_fonts[name];
}

const std::map<std::string, Font *> &ResourceManager::InternalGetFontMap() {
    return m_fonts;
}

Sprite *ResourceManager::CreateSprite(const std::string &name, Texture *texture)
{
    Sprite* sprite = new Sprite();

    sprite->texture = texture;
    m_sprites[name] = sprite;

    return sprite;
}

Sprite *ResourceManager::GetSprite(const std::string &name)
{
    if (m_sprites.find(name) == m_sprites.end())
    {
        ENGINE_LOG_ERROR("There is no Sprite with that name!");
    }

    return m_sprites[name];
}
