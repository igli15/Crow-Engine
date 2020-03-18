//
// Created by Igli milaqi on 15/03/2020.
//

#include "ColorMaterial.h"
#include "../Model.h"
#include "../../Debug/Debug.h"
#include "../../Components/Light.h"
#include "../../Components/Transform.h"

void ColorMaterial::Render(Model *pModel, const glm::mat4 &pModelMatrix, const glm::mat4 &pViewMatrix, const glm::mat4 &pProjectionMatrix,const glm::vec3& viewPos,World* world)
{
    m_shader->Use();

    ///ENGINE_LOG(world->EntitiesWith<Light>().size());

    auto lightEntities = world->EntitiesWith<Light,Transform>();

    auto lightComponent = world->GetComponent<Light>(lightEntities[0]);
    auto lightTransform = world->GetComponent<Transform>(lightEntities[0]);

    glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv(m_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));
    glUniform3fv(m_uSpecularColor,1,glm::value_ptr(specularColor));
    glUniform1f(m_uAmbientIntensity,ambientIntensity);
    glUniform1f(m_uShininess,shininess);

    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));

    glUniform3fv(m_uViewPos,1,glm::value_ptr(viewPos));

    glUniform3fv(m_uLightColor,1,glm::value_ptr(lightComponent.color));
    glUniform3fv(m_uLightDir,1,glm::value_ptr(lightTransform.GetLocalTransform()[2]));

    pModel->Draw(*m_shader);
}

ColorMaterial::ColorMaterial(const std::string &shaderName) : AbstractMaterial(shaderName)
{
    Initialize();
}

void ColorMaterial::Initialize()
{
    m_uModelMatrix = m_shader->GetUniformLocation("model");
    m_uViewMatrix = m_shader->GetUniformLocation("view");
    m_uProjectionMatrix = m_shader->GetUniformLocation("projection");

    m_uMainColor = m_shader->GetUniformLocation("material.mainColor");
    m_uSpecularColor = m_shader->GetUniformLocation("material.specularColor");
    m_uAmbientIntensity = m_shader->GetUniformLocation("material.ambientIntensity");
    m_uShininess = m_shader->GetUniformLocation("material.shininess");

    m_uViewPos = m_shader->GetUniformLocation("viewPos");
    m_uLightDir = m_shader->GetUniformLocation("light.direction");
    m_uLightColor = m_shader->GetUniformLocation("light.color");

}
