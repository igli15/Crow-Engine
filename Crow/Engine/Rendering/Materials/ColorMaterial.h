//
// Created by Igli milaqi on 15/03/2020.
//

#ifndef CROW_COLORMATERIAL_H
#define CROW_COLORMATERIAL_H

#include "../AbstractMaterial.h"

class ColorMaterial :public AbstractMaterial {

public:
    ColorMaterial(const std::string& shaderName);

    void Render(Model* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;
    void Initialize();

    glm::vec3 diffuseColor = glm::vec3(1);

private:

    GLint m_uProjectionMatrix = 0;
    GLint m_uViewMatrix = 0;
    GLint m_uModelMatrix = 0;
    GLint m_uDiffuseColor = 0;


};


#endif //CROW_COLORMATERIAL_H
