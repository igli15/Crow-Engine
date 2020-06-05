//
// Created by Igli milaqi on 05/04/2020.
//

#include "SpriteMaterial.h"

#include "../../Rendering/Shader.h"
#include "../../Components/SpriteInfo.h"
#include "../../Core/Game.h"
#include "../../Core/ResourceManager.h"

SpriteMaterial::SpriteMaterial() : AbstractMaterial("spriteShader")
{
    Initialize();
}

void SpriteMaterial::Initialize()
{
    m_shader->SetInt("image",0);
    m_uProjection = m_shader->GetUniformLocation("projection");
    m_uSpriteColor = m_shader->GetUniformLocation("spriteColor");
    m_uModel = m_shader->GetUniformLocation("model");
}

void SpriteMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    glUniform3fv(m_uSpriteColor, 1, glm::value_ptr(color));
}

void SpriteMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                          const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    m_shader->bufferedThisFrame = true;

    glUniformMatrix4fv(m_uProjection, 1, GL_FALSE, glm::value_ptr(pPerspectiveMatrix));
}

void SpriteMaterial::BufferModelUniform(const glm::mat4 &pModelMatrix)
{
    AbstractMaterial::BufferModelUniform(pModelMatrix);

    glUniformMatrix4fv(m_uModel, 1, GL_FALSE, glm::value_ptr(pModelMatrix));
}
