//
// Created by Igli milaqi on 25/03/2020.
//

#ifndef CROW_COLLISIONDETECTIONSYSTEM_H
#define CROW_COLLISIONDETECTIONSYSTEM_H


#include "../Feather/System.h"
#include "../Feather/EntityHandle.h"
#include <unordered_map>

class CollisionDetectionSystem : public System{

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
public:
    void Update(float dt) override;
};


#endif //CROW_COLLISIONDETECTIONSYSTEM_H
