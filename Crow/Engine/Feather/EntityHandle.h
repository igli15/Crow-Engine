//
// Created by Igli milaqi on 27/02/2020.
//

#ifndef CROW_ENTITYHANDLE_H
#define CROW_ENTITYHANDLE_H

#include "Types.h"
#include "World.h"

///A small wrapper for the entity.
///It provides a more "GameObject" style of programming which is more intuitive is certain cases.
///Instead of doing world->AddComponent(entity,component) you do entityHandle->AddComponent(component) instead.
struct EntityHandle {

    Entity entity;
    World* feather;

    ///Adds a component of a certain type to the entity.
    ///@param component The component which is going to be added.
    template <typename T>
    T* AddComponent(T component)
    {
        return feather->AddComponent(entity,component);
    }

    ///Removes a component of a certain type to the entity.
    template <typename T>
    void RemoveComponent()
    {
        feather->RemoveComponent<T>(entity);
    }

    ///Get a component of a certain type from the entity.
    ///@return Returns a "ComponentHandle<T>" which can contain a valid component pointer or a nullptr if no component was found.
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
