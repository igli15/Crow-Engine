//
// Created by Igli milaqi on 27/02/2020.
//

#ifndef CROW_COMPONENTHANDLER_H
#define CROW_COMPONENTHANDLER_H


#include "Types.h"
#include "ComponentArray.h"


template<typename T>
struct ComponentHandle {

    Entity owner;
    T* component;
    ComponentArray<T>* manager;

    ComponentHandle(){};

    ComponentHandle(Entity pE,ComponentArray<T>* pManager)
    {
        owner = pE;
        manager = pManager;

        if(manager != nullptr)
        {
            component = &(manager->GetComponentData(owner));
        }
        else
        {
            ENGINE_LOG_CRITICAL("ComponentHandle couldn't find component data of the owner");
            component = nullptr;
        }
    }


    //TODO not really the best implementation now it just brute force removes the component
    void Destroy()
    {
        manager->RemoveComponentData(owner);
    }
};


#endif //CROW_COMPONENTHANDLER_H
