//
// Created by Igli milaqi on 05/04/2020.
//

#ifndef CROW_SPRITERENDERERSYSTEM_H
#define CROW_SPRITERENDERERSYSTEM_H


#include <glm/glm.hpp>
#include <unordered_map>
#include "../Feather/System.h"
#include "../Rendering/Sprite.h"
#include "../Components/SpriteInfo.h"
#include "../Events/ComponentAddedEvent.h"

struct SpriteInstancedData
{
    Sprite* sprite;
    std::vector<glm::mat4>* modelMatrices;
};

class SpriteRendererSystem : public System
{
public:
    void Init() override;
    void Render() override;
    void OnCreate() override;
    void OnSpriteInfoAdded(ComponentAddedEvent<SpriteInfo>* event);

private:
    glm::mat4 m_projectionMatrix;
    std::unordered_map<int,SpriteInstancedData> m_instancedModelMap;
};


#endif //CROW_SPRITERENDERERSYSTEM_H
