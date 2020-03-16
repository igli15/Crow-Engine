//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_SYSTEMMANAGER_H
#define CROW_SYSTEMMANAGER_H


#include <typeinfo>
#include "../Debug/Debug.h"
#include "System.h"
#include <unordered_map>

class SystemManager {

public:
    template <typename T>
    T* RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        if(m_systems.find(typeName) != m_systems.end())
        {
            ENGINE_LOG_CRITICAL("System is already Registered");
        }

        T* system = new T();
        m_systems.insert({typeName,system});
        return system;
    }

    template <typename T>
    void SetSignature(EntitySignature signature)
    {
        const char* typeName = typeid(T).name();

        if(m_systems.find(typeName) == m_systems.end())
        {
            ENGINE_LOG_CRITICAL("System is NOT Registered");
        }

        m_signatures[typeName] = signature;
    }

    void OnEntityDestroyed(Entity entity)
    {
        for (auto const& pair : m_systems)
        {
            auto const& system = pair.second;

            system->m_entities.erase(entity);
        }
    }

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

    //TODO more maps here = more cache misses
    std::unordered_map<const char*,EntitySignature> m_signatures {};
    std::unordered_map<const char*,System*> m_systems {};
};


#endif //CROW_SYSTEMMANAGER_H
