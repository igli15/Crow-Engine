//
// Created by Igli milaqi on 06/05/2020.
//

#ifndef CROW_PROJECTILESYSTEM_H
#define CROW_PROJECTILESYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../Components/ProjectileComponent.h"
#include "../../Engine/Events/ComponentAddedEvent.h"

class ProjectileSystem : public System
{
public:
    void OnCreate() override;

    void OnProjectileComponentAdded(ComponentAddedEvent<ProjectileComponent>* event);
};


#endif //CROW_PROJECTILESYSTEM_H
