//
// Created by Igli milaqi on 15/03/2020.
//

#include "ColorMaterial.h"
#include "../Model.h"
#include "../../Debug/Debug.h"

void ColorMaterial::Render(Model *pModel, const glm::mat4 &pModelMatrix, const glm::mat4 &pViewMatrix, const glm::mat4 &pProjectionMatrix)
{
    m_shader->Use();

    glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pProjectionMatrix));
    glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
    glUniformMatrix4fv(m_uModelMatrix, 1, GL_FALSE, glm::value_ptr(pModelMatrix));

    glUniform3fv(m_uDiffuseColor,1,glm::value_ptr(diffuseColor));

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

    m_uDiffuseColor = m_shader->GetUniformLocation("diffuseColor");
}
