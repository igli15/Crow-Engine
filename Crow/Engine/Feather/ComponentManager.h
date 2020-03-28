//
// Created by Igli milaqi on 15/02/2020.
//

#ifndef CROW_COMPONENTMANAGER_H
#define CROW_COMPONENTMANAGER_H

#include <unordered_map>
#include "Types.h"
#include "ComponentArray.h"
#include "ComponentHandle.h"

class ComponentManager {

public:

    /*
    template <typename T>
    void RegisterComponent();

    template <typename T>
    ComponentType GetComponentType();
     */

    template <typename T>
    T* AddComponent(Entity entity,T component);

    template <typename T>
    void RemoveComponent(Entity entity);

    template <typename T>
    T& GetComponent(Entity entity);

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

    template <typename T>
    ComponentArray<T>* GetComponentArray();

private:

    std::array<IComponentArray*,MAX_COMPONENTS> m_allComponentArrays;
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



#endif //CROW_COMPONENTMANAGER_H
