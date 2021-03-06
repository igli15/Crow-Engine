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

//bool (*comparisonFcn)(int, int)
//using customComponentFunction = std::function<void(rapidxml::xml_node<>*,EntityHandle)>;
using customComponentFunction =  void (*)(rapidxml::xml_node<>*, EntityHandle);

class UnitySceneParser
{


public:
    static void ParseUnityScene(const std::string& fileName, World* currentWorld,customComponentFunction function = nullptr);

    //XML Util functions
    static glm::vec3 ScanVector3f(const char* charLine);
    static glm::quat ScanQuaternion(const char* charLine);

private:

    static void ParseAllEntities(rapidxml::xml_node<> *node,World* world,customComponentFunction function = nullptr);
    static EntityHandle ParseEntity(rapidxml::xml_node<>* node,World* world,customComponentFunction function = nullptr);
    static void ParseComponents(rapidxml::xml_node<>* com,EntityHandle newNode,customComponentFunction function = nullptr);
    static void ParseChildrenEntities(rapidxml::xml_node<>* com,EntityHandle entity,World* world,customComponentFunction function = nullptr);

    static void ParseEntityCore(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseLightComponent(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseCameraComponent(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseTranslucentMaterial(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseColorMaterial(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseTextureMaterial(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseAudioListener(rapidxml::xml_node<>* node,EntityHandle entityHandle);
    static void ParseAudioSource(rapidxml::xml_node<>* node,EntityHandle entityHandle);



};


#endif //CROW_UNITYSCENEPARSER_H
