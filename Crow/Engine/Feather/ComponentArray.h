//
// Created by Igli milaqi on 15/02/2020.
//

#ifndef CROW_COMPONENTARRAY_H
#define CROW_COMPONENTARRAY_H

#include "../../Crow.h"
#include <array>
#include <unordered_map>

class IComponentArray {

public:
    virtual ~IComponentArray() = default;
    virtual void OnEntityDestroyed(Entity entity) = 0;
    virtual std::vector<Entity> GetEntities() = 0;
    size_t validSize = 0;
};

template <typename T>
class ComponentArray : public IComponentArray {

public:

    T* AddComponentData(Entity entity,T Component)
    {
        if(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
        {
            ENGINE_LOG_CRITICAL("Component is already added");
        }

        size_t index = validSize;

        m_entityToIndexMap[entity] = index;
        m_indexToEntityMap[index] = entity;
        m_componentsArray[index] = Component;

        ++validSize;

        return &(m_componentsArray[index]);
    }

    void RemoveComponentData(Entity entity)
    {
        if(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end())
        {
            ENGINE_LOG_CRITICAL("Component is not added");
        }

        size_t indexOfElementToRemove = m_entityToIndexMap[entity];
        size_t indexOfLastElement = validSize - 1;

        m_componentsArray[indexOfElementToRemove] =  m_componentsArray[indexOfLastElement];

        Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];

        m_entityToIndexMap[entityOfLastElement] = indexOfElementToRemove;
        m_indexToEntityMap[indexOfElementToRemove] = entityOfLastElement;

        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(indexOfLastElement);

        --validSize;
    }

    T& GetComponentData(Entity entity)
    {
        auto it = m_entityToIndexMap.find(entity);

        if(it == m_entityToIndexMap.end())
        {
            ENGINE_LOG_CRITICAL("Component is not added");
        }

        return m_componentsArray[it->second];
    }

    void OnEntityDestroyed(Entity entity) override
    {
        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
        {
            RemoveComponentData(entity);
        }
    }

    Entity GetEntityFromIndex(size_t index)
    {
        return m_indexToEntityMap[index];
    }

    std::vector<Entity> GetEntities() override
    {
        std::vector<Entity> result{};

        for (auto it = m_entityToIndexMap.begin(); it != m_entityToIndexMap.end() ; it++)
        {
            result.push_back(it->first);
        }

        return result;
    }

    bool ContainsEntity(Entity entity)
    {
        auto iterator = m_entityToIndexMap.find(entity);

        return (iterator != m_entityToIndexMap.end());
    }


private:
    std::array<T,MAX_ENTITIES> m_componentsArray;

    //TODO: Change them to be a vector of tuples instead of a map. map will have a cache miss when trying to acces the key value pair.

    std::unordered_map<Entity,size_t> m_entityToIndexMap;
    std::unordered_map<size_t ,Entity> m_indexToEntityMap;


};






#endif //CROW_COMPONENTARRAY_H
