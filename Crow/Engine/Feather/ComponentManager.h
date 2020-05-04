//
// Created by Igli milaqi on 15/02/2020.
//

#ifndef CROW_COMPONENTMANAGER_H
#define CROW_COMPONENTMANAGER_H

#include <unordered_map>
#include "Types.h"
#include "ComponentArray.h"
#include "ComponentHandle.h"


///"ComponentManager" Keeps track of all "ComponentArrays" and notifies them if an entity got removed from the world
///All the ComponentArrays pointers are stored in an array and the location of the arrays is their type ID.
class ComponentManager {

public:

    ///Finds an component array of Type "T" and updates it correctly with the new entity and component
    ///@param entity the entity which the component will be added to.
    ///@param component the component that's going to be added.
    ///@return a pointer to the added component
    template <typename T>
    T* AddComponent(Entity entity,T component);

    template <typename T>
    void RemoveComponent(Entity entity);

    ///Finds an component array of Type "T" and get the component
    ///@param entity the entity which the component will be taken from
    template <typename T>
    T& GetComponent(Entity entity);


    ///Finds an component array of Type "T" and get the component pointer
    ///@param entity the entity which the component pointer will be searched for
    template <typename T>
    T* GetComponentPtr(Entity entity);

    ///Notifies all the active component arrays if an Entity got destroyed
    ///and if so update them accordingly
    void OnEntityDestroyed(Entity entity)
    {
        for (int i = 0; i<arrayCount ; ++i)
        {
            if(m_allComponentArrays[i] != nullptr)
            {
                m_allComponentArrays[i]->OnEntityDestroyed(entity);
            }
        }
    }

    ///Get an component array of a specified type "T"
    template <typename T>
    ComponentArray<T>* GetComponentArray();

private:

    ///All the component array pointers. size = max number of components
    std::array<IComponentArray*,MAX_COMPONENTS> m_allComponentArrays;

    ///The active count for the "m_allComponentArrays" array.
    int arrayCount = 0;
};


template<typename T>
ComponentArray<T> *ComponentManager::GetComponentArray()
{
    auto array = static_cast<ComponentArray<T>*>(m_allComponentArrays[ComponentIDGenerator::index<T>]);

    if(array == nullptr)
    {
        array = new ComponentArray<T>;
        m_allComponentArrays[ComponentIDGenerator::index<T>] = array;
        arrayCount++;
        return array;
    } else
    {
        return array;
    }

}

template<typename T>
T* ComponentManager::AddComponent(Entity entity,T component)
{
    return GetComponentArray<T>()->AddComponentData(entity,component);
}

template<typename T>
void ComponentManager::RemoveComponent(Entity entity)
{
    GetComponentArray<T>()->RemoveComponentData(entity);
}

template<typename T>
T &ComponentManager::GetComponent(Entity entity)
{
    return GetComponentArray<T>()->GetComponentData(entity);
}

template<typename T>
T *ComponentManager::GetComponentPtr(Entity entity)
{
    ComponentArray<T>* arrayPtr = GetComponentArray<T>();

    if(arrayPtr == nullptr) return nullptr;

    return arrayPtr->GetComponentPtr(entity);
}


#endif //CROW_COMPONENTMANAGER_H
