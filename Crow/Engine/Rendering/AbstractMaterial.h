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


class AbstractMaterial {

    friend class BufferMaterialsSystem;

public:
    AbstractMaterial(const std::string& shaderName);

    virtual void BufferMaterialUniforms(){};

    virtual void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                                        const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world){};

    int activeInstanceCount = 0;

    Shader* GetShader();

protected:
    Shader* m_shader;
};


#endif //CROW_ABSTRACTMATERIAL_H
