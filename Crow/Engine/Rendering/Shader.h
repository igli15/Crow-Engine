//
// Created by Igli milaqi on 06/03/2020.
//

#ifndef CROW_SHADER_H
#define CROW_SHADER_H

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/ext.hpp>


class Shader {

public:

    unsigned int ID;

    Shader(const std::string& vertexPath,const std::string&  fragmentPath);

    void Use();

    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetMat4(const std::string &name,const glm::mat4& m4);

    GLuint GetUniformLocation(const std::string& pName);
    GLuint GetAttribLocation(const std::string& pName);
};


#endif //CROW_SHADER_H
