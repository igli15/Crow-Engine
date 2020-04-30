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

    AbstractGroupArchetype* CreateUnitGroupArchetype(const std::string& name);
    AbstractGroupArchetype* GetUnitGroupArchetype(const std::string& name);


    static void ParseGameComponents(rapidxml::xml_node<>* node,EntityHandle entity);

private:
    std::unordered_map<std::string,AbstractGroupArchetype*> m_unitArchetypeMap;
};


#endif //CROW_MAINWORLD_H
