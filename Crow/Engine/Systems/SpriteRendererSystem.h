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


class Camera;
class Transform;

class SpriteRendererSystem : public System
{
public:
    void Render() override;
    void Init() override;

private:
    glm::mat4 m_projectionMatrix = glm::mat4(1);

    Camera* m_camera = nullptr;
    Transform* m_cameraTransform = nullptr;

};


#endif //CROW_SPRITERENDERERSYSTEM_H
