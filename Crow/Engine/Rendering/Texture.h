//
// Created by Igli milaqi on 07/03/2020.
//

#ifndef CROW_TEXTURE_H
#define CROW_TEXTURE_H

#include <GL/glew.h>

struct Texture {

public:
    const unsigned char* data;
    float nrOfChannels;

    GLuint ID;

    GLuint width;
    GLuint height;

    GLuint internalFormat; // Format of texture object
    GLuint imageFormat; // Format of loaded image

    // Texture configuration
    GLuint wrapS; // Wrapping mode on S axis
    GLuint wrapT; // Wrapping mode on T axis
    GLuint filterMin; // Filtering mode if texture pixels < screen pixels
    GLuint filterMax; // Filtering mode if texture pixels > screen pixels

    Texture(GLuint pInternalFormat = GL_RGBA,GLuint pImageFormat = GL_RGBA, GLuint pWrapS = GL_REPEAT,GLuint pWrapT = GL_REPEAT,
            GLuint pFilterMin = GL_LINEAR, GLuint pFilterMax = GL_LINEAR);

    void Generate(GLuint width, GLuint height, unsigned char* data);
    void Bind();
};


#endif //CROW_TEXTURE_H
