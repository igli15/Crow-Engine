//
// Created by Igli milaqi on 07/03/2020.
//

#include "ResourceManager.h"
#include "../../Plugins/stb_image.h"
#include "../../Crow.h"

Texture* ResourceManager::LoadTexture(const std::string &path, const std::string &name)
{
    Texture* texture = new Texture();
    int width, height, nrChannels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load((TEXTURE_PATH + path).data(), &width, &height, &nrChannels, 0);

    if(!data)
    {
       ENGINE_LOG_ERROR("There is no texture in path: " + path);
    }

    texture->data = data;
    texture->width = width;
    texture->height = height;
    texture->nrOfChannels = nrChannels;

    m_textures[name] = texture;

    return texture;
}

Shader *ResourceManager::CreateShader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &name)
{
    Shader* shader = new Shader(vertexPath,fragmentPath);

    m_shaders[name] = shader;

    return shader;
}

Texture *ResourceManager::GetTexture(const std::string &name)
{
    //TODO Add Error checking here

    return m_textures[name];
}

Shader *ResourceManager::GetShader(const std::string &name)
{
    //TODO Add Error checking here
    return m_shaders[name];
}

Model *ResourceManager::LoadModel(const std::string &path, const std::string &name)
{
    Model* model = new Model(path.data());

    m_models[name] = model;

    return model;
}

Model *ResourceManager::GetModel(const std::string &name)
{
    //TODO Add Error checking here
    return m_models[name];
}
