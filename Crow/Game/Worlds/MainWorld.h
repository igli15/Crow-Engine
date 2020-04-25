//
// Created by Igli milaqi on 20/04/2020.
//

#ifndef CROW_MAINWORLD_H
#define CROW_MAINWORLD_H


#include "../../Engine/Feather/World.h"
#include "../../Plugins/RapidXML/rapidxml.hpp"

#include <unordered_map>

class UnitGroupArchetype;

class MainWorld : public World
{
public:
    void Build() override;

    UnitGroupArchetype* CreateUnitGroupArchetype(const std::string& name);
    UnitGroupArchetype* GetUnitGroupArchetype(const std::string& name);


    static void ParseGameComponents(rapidxml::xml_node<>* node,EntityHandle entity);

private:
    std::unordered_map<std::string,UnitGroupArchetype*> m_unitArchetypeMap;
};


#endif //CROW_MAINWORLD_H
