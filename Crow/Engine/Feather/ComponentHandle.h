//
// Created by Igli milaqi on 27/02/2020.
//

#ifndef CROW_COMPONENTHANDLER_H
#define CROW_COMPONENTHANDLER_H


#include "Types.h"
#include "ComponentArray.h"

///Wrapper around component type.
///Contains info about the parent entity, a ptr to the actual component data and a ptr to the array of the component.
///Its returned from EntityHandle.GetComponent() and used by World.PopulateHandles().
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


    ///Internally destroys the component
    ///This will notify the systems or entities about the removal!
    ///Used internally
    void Destroy()
    {
        manager->RemoveComponentData(owner);
    }
};


#endif //CROW_COMPONENTHANDLER_H
