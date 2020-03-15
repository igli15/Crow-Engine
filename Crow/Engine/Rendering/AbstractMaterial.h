//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_ABSTRACTMATERIAL_H
#define CROW_ABSTRACTMATERIAL_H


#include "glm/glm.hpp"
#include <string>
#include "Shader.h"

class Model;


class AbstractMaterial {

public:
    AbstractMaterial(const std::string& shaderName);

    virtual void Render(Model* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pPerspectiveMatrix) = 0;

protected:
    Shader* m_shader;
};


#endif //CROW_ABSTRACTMATERIAL_H
