//
// Created by Igli milaqi on 14/05/2020.
//

#include "PortalMaterial.h"
#include "../../Core/Game.h"
#include <GLFW/glfw3.h>


PortalMaterial::PortalMaterial() : AbstractMaterial("portalShader")
{
    Initialize();
}

void PortalMaterial::Initialize()
{
    m_uMainColor = m_shader->GetUniformLocation("mainColor");
    m_uSecondColor = m_shader->GetUniformLocation("secondColor");
    m_uViewMatrix = m_shader->GetUniformLocation("view");
    m_uProjectionMatrix = m_shader->GetUniformLocation("projection");
    m_uTime = m_shader->GetUniformLocation("time");
    m_uNoiseTex = m_shader->GetUniformLocation("noiseTex");
    m_uRotationMask = m_shader->GetUniformLocation("rotationMask");
    m_uGlowMask = m_shader->GetUniformLocation("portalGlowMask");

    m_uRotationSpeed =  m_shader->GetUniformLocation("rotationSpeed");
    m_uScalingSpeed =  m_shader->GetUniformLocation("scalingSpeed");
    m_uSwirlAmount =  m_shader->GetUniformLocation("swirlAmount");

    m_uViewPos = m_shader->GetUniformLocation("viewPos");

    m_uFogDensity = m_shader->GetUniformLocation("fogDensity");
    m_uFogGradient = m_shader->GetUniformLocation("fogGradient");
    m_uFogColor = m_shader->GetUniformLocation("fogColor");
}

void PortalMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));
    glUniform3fv(m_uSecondColor,1,glm::value_ptr(secondColor));
    glUniform1f(m_uTime,glfwGetTime());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, noiseTexture->ID);
    glUniform1i(m_uNoiseTex, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, rotationMaskTexture->ID);
    glUniform1i(m_uRotationMask, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, portalGlowMask->ID);
    glUniform1i(m_uGlowMask, 2);

    glUniform1f(m_uRotationSpeed,rotationSpeed);
    glUniform1f(m_uScalingSpeed,scalingSpeed);
    glUniform1f(m_uSwirlAmount,swirlAmount);

}

void PortalMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                          const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
    glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));

    glUniform3fv(m_uViewPos,1,glm::value_ptr(viewPos));

    glUniform1f(m_uFogDensity,Game::Instance()->fogData.fogDensity * 0.5f);
    glUniform1f(m_uFogGradient,Game::Instance()->fogData.fogGradient);

    glUniform3fv(m_uFogColor,1,glm::value_ptr(Game::Instance()->fogData.fogColor));
}

