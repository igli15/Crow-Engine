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

    template <typename T>
    void RegisterComponent();

    template <typename T>
    ComponentType GetComponentType();

    template <typename T>
    void AddComponent(Entity entity,T component);

    template <typename T>
    void RemoveComponent(Entity entity);

    template <typename T>
    T& GetComponent(Entity entity);

    void OnEntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_componentArrays)
        {
            auto const& component = pair.second;
            component->OnEntityDestroyed(entity);
        }
    }

    template <typename T>
    ComponentArray<T>* GetComponentArray();

private:

    //TODO get rid of the maps
    std::unordered_map<const char*, ComponentType> m_componentTypes{};

    std::unordered_map<const char*,IComponentArray*> m_componentArrays{};

    ComponentType m_componentTypeCount;



};

template<typename T>
void ComponentManager::RegisterComponent()
{
    const char* typeName = typeid(T).name();

    Debug::Assert(m_componentTypes.find(typeName) == m_componentTypes.end(),"Component is already registered");

    m_componentTypes[typeName] = m_componentTypeCount;

    m_componentArrays[typeName] = new ComponentArray<T>();

    m_componentTypeCount++;
}

template<typename T>
ComponentType ComponentManager::GetComponentType()
{
    const char* typeName = typeid(T).name();

    Debug::Assert(m_componentTypes.find(typeName) != m_componentTypes.end(),"Component is not registered");

    return m_componentTypes[typeName];

}

template<typename T>
ComponentArray<T> *ComponentManager::GetComponentArray()
{
    const char* typeName = typeid(T).name();

    Debug::Assert(m_componentTypes.find(typeName) != m_componentTypes.end(),"Component is not registered");

    //Debug::Log("hre");

    //TODO Keep in mind that a nullptr has to be returned here if it cant get the array

    return static_cast<ComponentArray<T> *> (m_componentArrays[typeName]);

}

template<typename T>
void ComponentManager::AddComponent(Entity entity,T component)
{
    GetComponentArray<T>()->AddComponentData(entity,component);
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
