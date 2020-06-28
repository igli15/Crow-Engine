//
// Created by Igli milaqi on 15/05/2020.
//

#include "UnlitMaterial.h"

UnlitMaterial::UnlitMaterial() : AbstractMaterial("unlitShader")
{
    Initialize();
}

void UnlitMaterial::Initialize()
{
    m_uMainColor = m_shader->GetUniformLocation("mainColor");
    m_uViewMatrix = m_shader->GetUniformLocation("view");
    m_uProjectionMatrix = m_shader->GetUniformLocation("projection");
    m_uDiffuseTexture = m_shader->GetUniformLocation("diffuseTexture");
}

void UnlitMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                         const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTexture->ID);
    glUniform1i(m_uDiffuseTexture, 0);

    glUniformMatrix4fv(m_uProjectionMatrix, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
    glUniformMatrix4fv(m_uViewMatrix, 1, GL_FALSE, glm::value_ptr(pViewMatrix));
}

void UnlitMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    glUniform3fv(m_uMainColor,1,glm::value_ptr(mainColor));
}
