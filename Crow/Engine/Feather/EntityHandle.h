//
// Created by Igli milaqi on 27/02/2020.
//

#ifndef CROW_ENTITYHANDLE_H
#define CROW_ENTITYHANDLE_H

#include "Types.h"
#include "World.h"

struct EntityHandle {

    Entity entity;
    World* feather;

    template <typename T>
    T* AddComponent(T component)
    {
        return feather->AddComponent(entity,component);
    }

    template <typename T>
    void RemoveComponent()
    {
        feather->RemoveComponent<T>(entity);
    }

    template <typename T>
    ComponentHandle<T> GetComponent()
    {
        ComponentHandle<T> componentHandle;
        feather->PopulateHandles(entity,componentHandle);
        return componentHandle;
    }

    EntityHandle& operator=(const EntityHandle& other)
    {
        entity = other.entity;
        feather = other.feather;
        return *this;
    }

    bool operator == (const EntityHandle &other) const
    {
        return(this->entity == other.entity);
    }

};


#endif //CROW_ENTITYHANDLE_H
