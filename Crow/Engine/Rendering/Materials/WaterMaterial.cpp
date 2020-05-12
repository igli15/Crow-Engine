//
// Created by Igli milaqi on 11/05/2020.
//

#include "WaterMaterial.h"
#include "../Texture.h"
#include "GLFW/glfw3.h"

WaterMaterial::WaterMaterial() : AbstractMaterial("waterShader")
{
    Initialize();
}

void WaterMaterial::Initialize()
{
    m_uMainColor = m_shader->GetUniformLocation("mainColor");
    m_uViewMatrix = m_shader->GetUniformLocation("view");
    m_uProjectionMatrix = m_shader->GetUniformLocation("projection");
    m_uWaveNoiseTexture = m_shader->GetUniformLocation("waveNoiseTex");
    m_uDepthGradientTexture = m_shader->GetUniformLocation("depthTex");

    m_uFoamTexture = m_shader->GetUniformLocation("foamGradientTex");
    m_uCausticsTexture = m_shader->GetUniformLocation("causticsTex");
    m_uTime = m_shader->GetUniformLocation("time");
}

void WaterMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, waveNoiseTexture->ID);
    glUniform1i(m_uWaveNoiseTexture, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, depthGradientTexture->ID);
    glUniform1i(m_uDepthGradientTexture, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, foamGradientTexture->ID);
    glUniform1i(m_uFoamTexture, 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, causticsTexture->ID);
    glUniform1i(m_uCausticsTexture, 3);


    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));
    glUniform1f(m_uTime,glfwGetTime());
}

void WaterMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                         const glm::vec3 &viewPos, World *world)
{

    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
    glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
}

