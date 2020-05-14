//
// Created by Igli milaqi on 14/05/2020.
//

#include "PortalMaterial.h"
#include <GLFW/glfw3.h>


PortalMaterial::PortalMaterial() : AbstractMaterial("portalShader")
{
    Initialize();
}

void PortalMaterial::Initialize()
{
    m_uMainColor = m_shader->GetUniformLocation("mainColor");
    m_uViewMatrix = m_shader->GetUniformLocation("view");
    m_uProjectionMatrix = m_shader->GetUniformLocation("projection");
    m_uTime = m_shader->GetUniformLocation("time");
}

void PortalMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));
    glUniform1f(m_uTime,glfwGetTime());

}

void PortalMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                          const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
    glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
}

