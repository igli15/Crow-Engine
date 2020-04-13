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

    bool operator==(AbstractMaterial& other) const
    {
       return ID == other.ID;
    }

    virtual void BufferMaterialUniforms(){};

    virtual void BufferShaderUniforms(const glm::mat4 &pViewMatrix,
                                        const glm::mat4 &pPerspectiveMatrix, const glm::vec3 &viewPos, World *world){};

    virtual void BufferModelUniform(const glm::mat4 &pModelMatrix){};

    int activeInstanceCount = 0;

    Shader* GetShader();

    std::string name;
    int ID = -1;

    std::vector<glm::mat4> modelMatrices;

    //TODO should be a renderable!
    std::set<Model*> models;

protected:
    Shader* m_shader = nullptr;
};


#endif //CROW_ABSTRACTMATERIAL_H
