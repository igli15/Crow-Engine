//
// Created by Igli milaqi on 20/04/2020.
//

#ifndef CROW_MAINWORLD_H
#define CROW_MAINWORLD_H


#include "../../Engine/Feather/World.h"
#include "../../Plugins/RapidXML/rapidxml.hpp"

class MainWorld : public World
{
public:
    void Build() override;

    static void ParseGameComponents(rapidxml::xml_node<>* node,EntityHandle entity);
};


#endif //CROW_MAINWORLD_H
