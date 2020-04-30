//
// Created by Igli milaqi on 20/04/2020.
//

#ifndef CROW_MAINWORLD_H
#define CROW_MAINWORLD_H


#include "../../Engine/Feather/World.h"
#include "../../Plugins/RapidXML/rapidxml.hpp"

#include <unordered_map>

class AbstractGroupArchetype;

class MainWorld : public World
{
public:
    void Build() override;

    template<typename T>
    T* CreateUnitGroupArchetype(const std::string& name)
    {
        auto iterator = m_unitArchetypeMap.find(name);

        if (iterator != m_unitArchetypeMap.end())
        {
            ENGINE_LOG_ERROR("There is already a model with name: " + name);
            throw;
        }

        T* unitGroupArchetype = new T();
        m_unitArchetypeMap.insert(iterator,std::make_pair(name,unitGroupArchetype));
        return unitGroupArchetype;
    }

    template<typename T>
    T* GetUnitGroupArchetype(const std::string& name)
    {
        auto iterator = m_unitArchetypeMap.find(name);

        if (iterator == m_unitArchetypeMap.end())
        {
            return nullptr;
        }
        else
        {
            return static_cast<T*>(iterator->second);
        }
    }


    static void ParseGameComponents(rapidxml::xml_node<>* node,EntityHandle entity);

private:
    std::unordered_map<std::string,AbstractGroupArchetype*> m_unitArchetypeMap;
};


#endif //CROW_MAINWORLD_H
