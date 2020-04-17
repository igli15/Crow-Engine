//
// Created by Igli milaqi on 11/04/2020.
//

#ifndef CROW_UNITYSCENEPARSER_H
#define CROW_UNITYSCENEPARSER_H

#include <string>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_float.hpp>
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

    static void ParseEntityCore(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseLightComponent(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseCameraComponent(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseTranslucentMaterial(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseColorMaterial(rapidxml::xml_node<>* node,EntityHandle entityHandle);

    //XML Util functions
    static glm::vec3 ScanVector3f(const char* charLine);
    static glm::quat ScanQuaternion(const char* charLine);


};


#endif //CROW_UNITYSCENEPARSER_H
