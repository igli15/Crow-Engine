//
// Created by Igli milaqi on 11/04/2020.
//

#ifndef CROW_UNITYSCENEPARSER_H
#define CROW_UNITYSCENEPARSER_H

#include <string>
#include "../../Plugins/RapidXML/rapidxml.hpp"
#include "../Feather/EntityHandle.h"


class UnitySceneParser
{
public:
    static void ParseUnityScene(const std::string& fileName, World* currentWorld);

private:

    static void ParseAllEntities(rapidxml::xml_node<> *node,World* world);
    static EntityHandle ParseEntity(rapidxml::xml_node<>* node,World* world);
    static void ParseComponents(rapidxml::xml_node<>* com,EntityHandle newNode);

};


#endif //CROW_UNITYSCENEPARSER_H
