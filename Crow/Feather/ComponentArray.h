//
// Created by Igli milaqi on 15/02/2020.
//

#ifndef CROW_COMPONENTARRAY_H
#define CROW_COMPONENTARRAY_H

#include "Types.h"
#include <array>
#include <unordered_map>
#include "../Debug/Debug.h"

//TODO Get rid of this interface... use events or reflection to solve the "OnEntityDestroyed" callbacks
class IComponentArray {

public:
    virtual ~IComponentArray() = default;
    virtual void OnEntityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {

public:

    void AddComponentData(Entity entity,T Component);
    void RemoveComponentData(Entity entity);

    T& GetComponentData(Entity entity);

    void OnEntityDestroyed(Entity entity) override;

private:
    std::array<T,MAX_ENTITIES> m_componentsArray;

    //TODO: Change them to be a vector of tuples instead of a map. map will have a cache miss when trying to acces the key value pair.

    std::unordered_map<Entity,size_t> m_entityToIndexMap;
    std::unordered_map<size_t ,Entity> m_indexToEntityMap;

    size_t m_validSize;
};

template<typename T>
void ComponentArray<T>::AddComponentData(Entity entity, T Component)
{
    Debug::Assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end(),"Component is already added");

    size_t index = m_validSize;
    m_entityToIndexMap[entity] = index;
    m_indexToEntityMap[index] = entity;
    m_componentsArray[index] = Component;

    ++m_validSize;
}

template<typename T>
void ComponentArray<T>::RemoveComponentData(Entity entity)
{
    Debug::Assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(),"Component is not added");

    size_t indexOfElementToRemove = m_entityToIndexMap[entity];
    size_t indexOfLastElement = m_validSize - 1;

    m_componentsArray[indexOfElementToRemove] =  m_componentsArray[indexOfLastElement];

    Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];
    m_entityToIndexMap[entityOfLastElement] = indexOfElementToRemove;
    m_indexToEntityMap[indexOfElementToRemove] = entityOfLastElement;

    m_entityToIndexMap.erase(entity);
    m_indexToEntityMap.erase(indexOfElementToRemove);

    --m_validSize;
}

template<typename T>
T &ComponentArray<T>::GetComponentData(Entity entity)
{
    //Debug::Assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end(),"Component is not added");

    return m_componentsArray[m_entityToIndexMap[entity]];
}

template<typename T>
void ComponentArray<T>::OnEntityDestroyed(Entity entity)
{
    if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
    {
        RemoveComponentData(entity);
    }
}


#endif //CROW_COMPONENTARRAY_H
