//
// Created by Igli milaqi on 30/03/2020.
//

#ifndef CROW_XMLWORLD_H
#define CROW_XMLWORLD_H


#include "../Feather/World.h"
#include "../../Plugins/RapidXML/rapidxml.hpp"


//XMLWorld will load itself from an xml file which is exported from Unity3D
class XMLWorld : public World {

public:
    void Build() override;

protected:
    void Load(const std::string& sceneName);
    void ParseAllEntities(rapidxml::xml_node<> *node, EntityHandle entity, bool isRoot = false);
    EntityHandle ParseEntity(rapidxml::xml_node<>* node);
    void ParseChildren(rapidxml::xml_node<>* node, EntityHandle entity);
    void ParseComponents(rapidxml::xml_node<>* com,EntityHandle newNode);
};


#endif //CROW_XMLWORLD_H
