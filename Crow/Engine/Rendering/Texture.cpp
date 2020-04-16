//
// Created by Igli milaqi on 07/03/2020.
//

#include "Texture.h"

void Texture::Generate(GLuint pwidth, GLuint pheight, unsigned char *data)
{
    this->width = pwidth;
    this->height = pheight;

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

Texture::Texture(GLuint pInternalFormat, GLuint pImageFormat, GLuint pWrapS, GLuint pWrapT, GLuint pFilterMin,
                 GLuint pFilterMax) : internalFormat(pInternalFormat),imageFormat(pImageFormat),wrapS(pWrapS),wrapT(pWrapT),filterMin(pFilterMin)
                 ,filterMax(pFilterMax)
{
    glGenTextures(1,&ID);
}
