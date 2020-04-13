//
// Created by Igli milaqi on 06/04/2020.
//

#include "SpriteRenderingWorld.h"
#include "../../Engine/Rendering/Texture.h"
#include "../../Engine/Core/Game.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/SpriteInfo.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Core/ResourceManager.h"
#include "../../Engine/Components/Camera.h"
#include "../../Engine/Rendering/Materials/SpriteMaterial.h"

void SpriteRenderingWorld::Build()
{
    World::Build();

    EntityHandle cameraEntity = CreateEntity();
    cameraEntity.AddComponent(Camera{});
    cameraEntity.AddComponent(Transform{})->Translate(glm::vec3(0,0,0));

    Texture* texture = Game::Instance()->resourceManager->LoadTexture(TEXTURE_PATH + "crowIcon.png","crowTexture");
    Sprite* sprite = Game::Instance()->resourceManager->CreateSprite("crowSprite",texture);
    SpriteMaterial* spriteMaterial = Game::Instance()->resourceManager->CreateMaterial<SpriteMaterial>("spriteMat");

    if(spriteMaterial == nullptr) throw;

    EntityHandle spriteEntity = CreateEntity();
    Transform* spriteTransform = spriteEntity.AddComponent(Transform{});
    spriteTransform->SetLocalPosition(glm::vec3(200,200,0));
    spriteTransform->Scale(glm::vec3(200,200,1));
    SpriteInfo spriteInfo{};
    spriteInfo.sprite = sprite;
    spriteInfo.material = spriteMaterial;
    spriteInfo.SetColor(glm::vec3(1,0,1));
    spriteEntity.AddComponent(spriteInfo);

}
