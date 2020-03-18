//
// Created by Igli milaqi on 15/03/2020.
//

#ifndef CROW_COLORMATERIAL_H
#define CROW_COLORMATERIAL_H

#include "../AbstractMaterial.h"

class ColorMaterial :public AbstractMaterial {

public:
    ColorMaterial(const std::string& shaderName);

    void Render(Model* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix,const glm::vec3& viewPos,World* world) override;
    void Initialize();

    glm::vec3 mainColor = glm::vec3(1);
    glm::vec3 specularColor = glm::vec3(1);

    float shininess = 16;
    float ambientIntensity = 0.1f;

private:

    GLint m_uProjectionMatrix = 0;
    GLint m_uViewMatrix = 0;
    GLint m_uModelMatrix = 0;

    GLint m_uMainColor = 0;
    GLint m_uAmbientIntensity;
    GLint m_uShininess;
    GLint m_uSpecularColor;

    GLint m_uViewPos;
    GLint m_uLightDir;
    GLint m_uLightColor;
};


#endif //CROW_COLORMATERIAL_H
