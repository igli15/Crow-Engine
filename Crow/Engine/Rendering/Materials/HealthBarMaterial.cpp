//
// Created by Igli milaqi on 05/06/2020.
//


#include "HealthBarMaterial.h"
#include <GLFW/glfw3.h>

HealthBarMaterial::HealthBarMaterial() : AbstractMaterial("healthBarShader")
{
    Initialize();
}

void HealthBarMaterial::Initialize()
{
    m_shader->SetInt("image",0);
    m_uProjection = m_shader->GetUniformLocation("projection");
    m_uFilledColor = m_shader->GetUniformLocation("filledColor");
    m_uModel = m_shader->GetUniformLocation("model");
    m_uFillAmount = m_shader->GetUniformLocation("fillAmount");


    m_uNoiseMap = m_shader->GetUniformLocation("noise");
    m_uEmptyColor = m_shader->GetUniformLocation("emptyColor");
    m_uTime = m_shader->GetUniformLocation("time");
}

void HealthBarMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                             const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    m_shader->bufferedThisFrame = true;

    glUniformMatrix4fv(m_uProjection, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
}

void HealthBarMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    glUniform3fv(m_uFilledColor, 1, glm::value_ptr(fillColor));
    glUniform3fv(m_uEmptyColor, 1, glm::value_ptr(emptyColor));
    glUniform1f(m_uFillAmount,fillAmount);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, noiseMap->ID);
    glUniform1i(m_uNoiseMap, 1);

    glUniform1f(m_uTime,glfwGetTime());

}

void HealthBarMaterial::BufferModelUniform(const glm::mat4 &pModelMatrix)
{
    AbstractMaterial::BufferModelUniform(pModelMatrix);

    glUniformMatrix4fv(m_uModel, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
}
