//
// Created by Igli milaqi on 05/04/2020.
//

#include "SpriteMaterial.h"

#include "../../Rendering/Shader.h"
#include "../../Components/SpriteInfo.h"
#include "../../Core/Game.h"
#include "../../Core/ResourceManager.h"

void SpriteMaterial::RenderSprite(SpriteInfo *spriteInfo, const glm::mat4 &pModelMatrix,
                                  const glm::mat4 &pPerspectiveMatrix)
{
    shader->Use();

    this->shader->SetMat4("model", pModelMatrix);
    this->shader->SetMat4("projection", pPerspectiveMatrix);
    this->shader->SetVec3("spriteColor", spriteInfo->color);

}

SpriteMaterial::SpriteMaterial()
{
    shader = Game::Instance()->resourceManager->GetShader("spriteShader");
    shader->SetInt("image",0);
}
