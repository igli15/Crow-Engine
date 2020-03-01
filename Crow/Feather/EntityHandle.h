//
// Created by Igli milaqi on 27/02/2020.
//

#ifndef CROW_ENTITYHANDLE_H
#define CROW_ENTITYHANDLE_H

#include "Types.h"
#include "Feather.h"

struct EntityHandle {

    Entity entity;
    Feather* feather;

    template <typename T>
    void AddComponent(T component)
    {
        feather->AddComponent(entity,component);
    }

    template <typename T>
    void RemoveComponent(T component)
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

};


#endif //CROW_ENTITYHANDLE_H
