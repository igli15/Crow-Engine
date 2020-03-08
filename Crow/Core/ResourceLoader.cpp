//
// Created by Igli milaqi on 07/03/2020.
//

#include "ResourceLoader.h"
#include "../Plugins/stb_image.h"

Texture& ResourceLoader::LoadTexture(const std::string &path, const std::string &name)
{
    Texture* texture = new Texture();
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

    texture->data = data;
    texture->width = width;
    texture->height = height;
    texture->nrOfChannels = nrChannels;

    //m_textures[name] = texture;

    return *texture;
}
