//
// Created by Igli milaqi on 06/03/2020.
//

#ifndef CROW_SHADER_H
#define CROW_SHADER_H

#include "Gl/glew.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {

public:

    unsigned int ID;

    Shader(const std::string& vertexPath,const std::string&  fragmentPath);

    void Use();

    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;

};


#endif //CROW_SHADER_H
