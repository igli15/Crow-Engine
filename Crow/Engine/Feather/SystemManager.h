//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_SYSTEMMANAGER_H
#define CROW_SYSTEMMANAGER_H


#include <typeinfo>
#include "../Debug/Debug.h"
#include "System.h"
#include <unordered_map>


///Holds a refence to all the systems.
///Updates system signatures and the entity list for each system when needed.
///Creates and Registers systems.
class SystemManager {

public:

    ///Registers and creates a system of a certain type.
    ///If the system is already registered a error will be thrown!
    ///@return Returns a pointer to the created system.
    template <typename T>
    T* RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        if(m_systems.find(typeName) != m_systems.end())
        {
            ENGINE_LOG_CRITICAL("System is already Registered");
            throw;
        }

        T* system = new T();
        m_systems.insert({typeName,system});
        return system;
    }

    ///Set the signature of a system
    ///@param signature the new signature.
    template <typename T>
    void SetSignature(EntitySignature signature)
    {
        const char* typeName = typeid(T).name();

        if(m_systems.find(typeName) == m_systems.end())
        {
            ENGINE_LOG_CRITICAL("System is NOT Registered");
            throw;
        }

        m_signatures[typeName] = signature;
    }

    ///Called when an entity is destroyed from the world.
    ///Erases the entity from the system's set if needed.
    ///@param entity The entity which is about to be destroyed.
    void OnEntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_systems)
        {
            auto const& system = pair.second;

            system->m_entities.erase(entity);
        }
    }

    ///Called when the signature of an entity has changed.
    ///It checks if the new signature matches the signature of the system and if so it adds it to the set.
    ///@param entity Entity which signature changed
    ///@param signature The new EntitySignature
    void OnEntitySignatureChanged(Entity entity,EntitySignature signature)
    {
        for (auto const& pair : m_systems)
        {
            const char* typeName = pair.first;
            System* system = pair.second;
            EntitySignature systemSignature = m_signatures[typeName];

            if((signature & systemSignature) == systemSignature)
            {
                system->m_entities.insert(entity);
            }
            else
            {
                system->m_entities.erase(entity);
            }
        }
    }

private:

    std::unordered_map<const char*,EntitySignature> m_signatures {};
    std::unordered_map<const char*,System*> m_systems {};
};


#endif //CROW_SYSTEMMANAGER_H
