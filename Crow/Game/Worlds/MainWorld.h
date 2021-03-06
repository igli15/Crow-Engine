//
// Created by Igli milaqi on 20/04/2020.
//

#ifndef CROW_MAINWORLD_H
#define CROW_MAINWORLD_H


#include "../../Engine/Feather/World.h"
#include "../../Plugins/RapidXML/rapidxml.hpp"

#include <unordered_map>

class UnitGroupArchetype;
class ResourceManager;
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
            return iterator->second;
            //throw;
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
    void CreateUIEntities();

private:
    void CreateDebugText();
    void CreateMainMenu();

    std::unordered_map<std::string,UnitGroupArchetype*> m_unitArchetypeMap;

    void CreateMeleeArchetypes(unsigned int rows,unsigned int columns,float maxHorizontalDistance,float maxVerticalDistance,float scaleFactor,float maxSpeed,float maxHealth,float DamageRate,float colliderRadius,float moneyDrop,float moneyThroughPortal,float dmgThroughPortal,float unitPrice);
    void CreateTankArchetypes(unsigned int rows,unsigned int columns,float maxHorizontalDistance,float maxVerticalDistance,float scaleFactor,float maxSpeed,float maxHealth,float DamageRate,float colliderRadius,float moneyDrop,float moneyThroughPortal,float dmgThroughPortal,float unitPrice);
    void CreateCannonArchetypes(unsigned int rows,unsigned int columns,float maxHorizontalDistance,float maxVerticalDistance,float scaleFactor,float maxSpeed,float maxHealth,float DamageRate,float colliderRadius,float moneyDrop,float moneyThroughPortal,float dmgThroughPortal,float unitPrice);
};


#endif //CROW_MAINWORLD_H
