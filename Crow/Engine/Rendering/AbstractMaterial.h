//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_ABSTRACTMATERIAL_H
#define CROW_ABSTRACTMATERIAL_H


#include "glm/glm.hpp"
#include <string>
#include "Shader.h"
#include "../Feather/World.h"

class Model;

///AbstractMaterial is the base class for all the materials.
///It provides virtual methods which the materials should implement.
///Each Material Has it's own shader and buffers the shader's uniforms once.
class AbstractMaterial {

public:
    AbstractMaterial(const std::string& shaderName);

    bool operator==(AbstractMaterial& other) const
    {
       return ID == other.ID;
    }

    virtual void BufferMaterialUniforms(){};

    virtual void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                                        const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world){};

    virtual void BufferModelUniform(const glm::mat4 &pModelMatrix){};


    Shader* GetShader();

    std::string name;
    int ID = -1;

protected:
    Shader* m_shader = nullptr;
};


#endif //CROW_ABSTRACTMATERIAL_H
