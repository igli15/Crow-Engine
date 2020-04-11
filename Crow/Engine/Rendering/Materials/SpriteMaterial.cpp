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
    m_shader->SetInt("image",0);

    Initialize();
}

void SpriteMaterial::Initialize()
{
    //TODO get shader variables here once
}

void SpriteMaterial::BufferMaterialUniforms()
{
    AbstractMaterial::BufferMaterialUniforms();

    //TODO make color a property of this material
    this->m_shader->SetVec3("spriteColor", glm::vec3(1,1,1));
}

void SpriteMaterial::BufferShaderUniforms(const glm::mat4 &pViewMatrix, const glm::mat4 &pPerspectiveMatrix,
                                          const glm::vec3 &viewPos, World *world)
{
    AbstractMaterial::BufferShaderUniforms(pViewMatrix, pPerspectiveMatrix, viewPos, world);

    m_shader->Use();

    m_shader->SetMat4("projection", glm::ortho(0.0f, static_cast<GLfloat>(1920),
                                               static_cast<GLfloat>(1080), 0.0f, -1.0f, 1.0f));

}
