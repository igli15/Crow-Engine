//
// Created by Igli milaqi on 14/02/2020.
//

#ifndef CROW_ENTITYMANAGER_H
#define CROW_ENTITYMANAGER_H

#include <queue>
#include <array>
#include "Types.h"

class EntityManager {

public:
    EntityManager();

    Entity CreateEntity();
    void DestroyEntity(Entity e);
    void SetSignature(Entity e,EntitySignature s);
    EntitySignature GetSignature(Entity e);

private:
    std::queue<Entity> m_entityQueue{};


    //NOTE: Swaped the std:: array with a c style array here
    //std::array<EntitySignature,MAX_ENTITIES> m_signatures{};
    EntitySignature* m_signatures;

    int m_activeEntities = 0;
};


#endif