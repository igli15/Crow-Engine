//
// Created by Igli milaqi on 15/02/2020.
//

#ifndef CROW_COMPONENTARRAY_H
#define CROW_COMPONENTARRAY_H

#include "../../Crow.h"
#include "../EventQueue/EventQueue.h"
#include <array>
#include <unordered_map>
#include "../Events/ComponentRemovedEvent.h"

///This is the base class of all ComponentArrays.
///It is here so that the ComponentManager stores a reference to all ComponentArrays and some abstract method implementations.
class IComponentArray {

public:
    virtual ~IComponentArray() = default;

    ///Called when an entity is destroyed from the world.
    ///@param entity The entity which is about to be destroyed.
    virtual void OnEntityDestroyed(Entity entity) = 0;

    ///Returns a std::vector of all entities that the components in the array are attached to.
    virtual std::vector<Entity> GetEntities() = 0;

    ///The active component count.
    size_t validSize = 0;
};

///Custom container which stores contagiously a collection of specified types.
///Every element is allocated once and pooled meaning the array size is equal to the maximum number of entities.
///When a element is removed it is swapped with the last element and the indexes are updated.
///template <typename T> Is the component type which will be stored.
template <typename T>
class ComponentArray : public IComponentArray {

public:

    ///Adds a component to the specified entity.
    ///@param entity The entity which the component will be added to.
    ///@param Component The component which will be stored on the array.
    ///@return A pointer to the component which was just added.
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

    ///Checks if the entity is an index in the array and if so it removes the component attached to it
    ///@param entity The entity which component will be removed
    void RemoveComponentData(Entity entity)
    {
        if(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end())
        {
            ENGINE_LOG_CRITICAL("Component is not added");
        }

        size_t indexOfElementToRemove = m_entityToIndexMap[entity];
        size_t indexOfLastElement = validSize - 1;

        //Copy of the component about to be removed
        T comp = m_componentsArray[indexOfElementToRemove];

        m_componentsArray[indexOfElementToRemove] =  m_componentsArray[indexOfLastElement];

        Entity entityOfLastElement = m_indexToEntityMap[indexOfLastElement];

        m_entityToIndexMap[entityOfLastElement] = indexOfElementToRemove;
        m_indexToEntityMap[indexOfElementToRemove] = entityOfLastElement;

        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(indexOfLastElement);

        --validSize;

        //Gets a copy of the removed component
        EventQueue::Instance().Publish(new ComponentRemovedEvent<T>(entity, comp));
    }

    ///Finds a component for a specified entity and returns a reference to it.
    ///@param entity the entity which component will be looked for.
    ///@return T& a reference to the component.
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

    std::vector<Entity> GetEntities() override
    {
        std::vector<Entity> result{};

        for (auto it = m_entityToIndexMap.begin(); it != m_entityToIndexMap.end() ; it++)
        {
            result.push_back(it->first);
        }

        return result;
    }

    ///Checks if the array contains an entity as an index to any of the components.
    ///@return Returns true if the entity is used as an index to the array otherwise returns false
    bool ContainsEntity(Entity entity)
    {
        auto iterator = m_entityToIndexMap.find(entity);

        return (iterator != m_entityToIndexMap.end());
    }


private:
    ///The internal array of components. size = the maximum number of entities in the world.
    std::array<T,MAX_ENTITIES> m_componentsArray;

    ///map from entity to an array index
    std::unordered_map<Entity,size_t> m_entityToIndexMap;

    ///map from an array index to entity
    std::unordered_map<size_t ,Entity> m_indexToEntityMap;


};






#endif //CROW_COMPONENTARRAY_H
