//
// Created by Igli milaqi on 19/05/2020.
//

#ifndef CROW_FLOCKSEPARATIONSYSTEM_H
#define CROW_FLOCKSEPARATIONSYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../Components/SteeringComponent.h"
#include "../../Engine/Components/Transform.h"
#include <vector>
class BridgeComponent;

class FlockSeparationSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

    glm::vec3 DoFlockingSeparation(Transform& ownTransform, const std::vector<Entity>& others,float separationDistance,float separationFactor =1);
private:
    std::vector<BridgeComponent*> m_bridges;

    float m_timeCounter = 1.5f;
};


#endif //CROW_FLOCKSEPARATIONSYSTEM_H
