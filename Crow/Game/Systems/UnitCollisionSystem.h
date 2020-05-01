//
// Created by Igli milaqi on 01/05/2020.
//

#ifndef CROW_UNITCOLLISIONSYSTEM_H
#define CROW_UNITCOLLISIONSYSTEM_H


#include "../../Engine/Feather/System.h"
#include "../../Engine/Feather/EntityHandle.h"

class UnitCollisionSystem : public System
{
public:
    void Init() override;
    void Update(float dt) override;

private:
    typedef std::pair<EntityHandle,EntityHandle> EntityPair;

    struct hash_EntityPair
    {
        size_t operator() (const EntityPair&  pair) const
        {
            int x = pair.first.entity;
            int y = pair.second.entity;

            //Cantor Pairing hashing
            return 0.5 * (x+y) * (x+y+1) + y;
        }
    };

    std::unordered_map<EntityPair,int,hash_EntityPair> m_collisionMap;
    int m_frameCounter = 0;

    void ThrowCollisionEvents();
};


#endif //CROW_UNITCOLLISIONSYSTEM_H
