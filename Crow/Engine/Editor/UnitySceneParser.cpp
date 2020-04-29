//
// Created by Igli milaqi on 11/04/2020.
//

#include <fstream>
#include "UnitySceneParser.h"
#include "../Feather/World.h"
#include "../Components/Transform.h"
#include "../Rendering/Model.h"
#include "../Core/Game.h"
#include "../Components/MeshInfo.h"
#include "../Core/ResourceManager.h"
#include "../Rendering/Materials/ColorMaterial.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"
#include "../Rendering/Materials/TranslucentColorMat.h"
#include "../Rendering/Materials/TextureMaterial.h"

void UnitySceneParser::ParseUnityScene(const std::string &fileName, World *currentWorld,customComponentFunction function )
{
    //Reads the xml file and gets the root node
    std::ifstream myXml(SCENE_PATH + fileName);
    std::vector<char> buffer((std::istreambuf_iterator<char>(myXml)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    rapidxml::xml_node<> *rootNode = doc.first_node("root");

    std::cout << "PARSING LEVEL....." << std::endl;

    if (rootNode == nullptr) {
        ENGINE_LOG_ERROR("XML Node is null!");
    }

    ParseAllEntities(rootNode,currentWorld,function);

}

void UnitySceneParser::ParseAllEntities(rapidxml::xml_node<> *node, World *world,customComponentFunction function )
{
    for (rapidxml::xml_node<> *currentObjectNode = node->first_node();
         currentObjectNode != nullptr; currentObjectNode = currentObjectNode->next_sibling())
    {
        if (strcmp(currentObjectNode->name(), "GameObject") == 0)
        {
            EntityHandle currentNode = ParseEntity(currentObjectNode,world,function);
            ParseChildrenEntities(currentObjectNode,currentNode,world,function);
        }

    }
}

EntityHandle UnitySceneParser::ParseEntity(rapidxml::xml_node<> *node, World *world,customComponentFunction function)
{
    EntityHandle entity = world->CreateEntity();

    ParseEntityCore(node,entity);

    if (strcmp(node->first_node()->name(), "Components") == 0) {
        rapidxml::xml_node<> *compNode = node->first_node();
        for (rapidxml::xml_node<> *com = compNode->first_node(); com != nullptr; com = com->next_sibling()) {
            ParseComponents(com, entity,function);
        }
    }

    return entity;
}

void UnitySceneParser::ParseChildrenEntities(rapidxml::xml_node<> *node, EntityHandle entity,World* world,customComponentFunction function)
{
    if (node->first_node()->next_sibling() != nullptr)
    {
        rapidxml::xml_node<> *childNode = node->first_node()->next_sibling();
        for (rapidxml::xml_node<> *com = childNode; com != nullptr; com = com->next_sibling())
        {
            if (strcmp(com->name(), "GameObject") == 0)
            {
                EntityHandle child = ParseEntity(com,world,function);
                Transform *childTransform = child.GetComponent<Transform>().component;
                Transform *parentTransform = entity.GetComponent<Transform>().component;

                childTransform->SetParent(entity.entity);

                //Parse the children of children recursively!
                ParseChildrenEntities(com,child,world,function);
            }
        }

    }
}



void UnitySceneParser::ParseComponents(rapidxml::xml_node<> *com, EntityHandle newNode,customComponentFunction function)
{
    if (strcmp(com->name(), "Camera") == 0)
    {
        ParseCameraComponent(com,newNode);
    }
    else if (strcmp(com->name(), "Light") == 0)
    {
        ParseLightComponent(com, newNode);
    }
    else if (strcmp(com->name(), "ColorMaterial") == 0)
    {
        ParseColorMaterial(com,newNode);
    }
    else if (strcmp(com->name(), "TranslucentMaterial") == 0)
    {
        ParseTranslucentMaterial(com,newNode);
    }
    else if (strcmp(com->name(), "TextureMaterial") == 0)
    {
        ParseTextureMaterial(com,newNode);
    }

    if(function != nullptr)
    {
        function(com, newNode);
    }
}

void UnitySceneParser::ParseEntityCore(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{
    Transform *entityTransform = entityHandle.AddComponent(Transform{});

    for (rapidxml::xml_attribute<> *a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute()) {
        std::string attributeName = a->name();

        if (attributeName == "position")
        {
            glm::vec3 pos = ScanVector3f(a->value());
            entityTransform->SetLocalPosition(pos);
        }
        else if (attributeName == "rotation")
        {
            glm::quat rot = ScanQuaternion(a->value());
            entityTransform->Rotate(rot);
            //entityTransform->Rotate(glm::angle(rot),glm::axis(rot));
        }
        else if (attributeName == "scale")
        {
            glm::vec3 scale = ScanVector3f(a->value());;
            entityTransform->Scale(scale);
        }
        else if (attributeName == "mesh")
        {
            Model *mesh = Game::Instance()->resourceManager->GetModel(a->value());

            MeshInfo meshInfo{mesh,Game::Instance()->resourceManager->GetMaterial<ColorMaterial>("defaultMat")};
            meshInfo.model = mesh;
            entityHandle.AddComponent(meshInfo);
        }

    }
}


void UnitySceneParser::ParseLightComponent(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{
    Light *light = entityHandle.AddComponent(Light{});

    for (rapidxml::xml_attribute<> *a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute()) {
        std::string attributeName = a->name();
        if (attributeName == "type") {
            std::string value(a->value());
            if (value == "DIRECTIONAL") {
                light->type = Light::DIRECTIONAL;
            } else if (value == "POINT") {
                light->type = Light::POINT;
            } else if (value == "SPOT") {
                light->type = Light::SPOT;
            }
        } else if (attributeName == "color")
        {
            light->color = ScanVector3f(a->value());
        } else if (attributeName == "intensity") {
            light->intensity = strtof(a->value(), 0);
        } else if (attributeName == "attenuationConstants")
        {
            glm::vec3 consts = ScanVector3f(a->value());
            light->constant = consts.x;
            light->linear = consts.y;
            light->quadratic = consts.z;
        } else if (attributeName == "cutoffAngle")
        {
            light->cutoff = strtof(a->value(), 0);
        } else if (attributeName == "outercutoffAngle")
        {
            light->outerCutoff = strtof(a->value(), 0);
        }

    }

}

void UnitySceneParser::ParseCameraComponent(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{
    Camera *cam = entityHandle.AddComponent(Camera{});

    for (rapidxml::xml_attribute<> *a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute()) {
        std::string attributeName = a->name();
        if (attributeName == "FOV") {
            cam->FOV = strtof(a->value(), 0);
        } else if (attributeName == "aspectRatio") {
            cam->aspectRatio = strtof(a->value(), 0);
        } else if (attributeName == "nearClipPlane") {
            cam->nearClipPlane = strtof(a->value(), 0);
        } else if (attributeName == "farClipPlane") {
            cam->farClipPlane = strtof(a->value(), 0);
        }
    }
}

void UnitySceneParser::ParseTranslucentMaterial(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{
    TranslucentColorMat* translucentColorMat;
    for (rapidxml::xml_attribute<> *a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute())
    {
        std::string attributeName = a->name();

        if (attributeName == "materialName")
        {
            std::string value(a->value());
            auto material = Game::Instance()->resourceManager->GetMaterial<TranslucentColorMat>(value);
            if(material == nullptr)
            {
                translucentColorMat = Game::Instance()->resourceManager->CreateMaterial<TranslucentColorMat>(value);
            }
            else
            {
                translucentColorMat = material;
            }

        }
        else if(attributeName == "mainColor")
        {
            translucentColorMat->mainColor = ScanVector3f(a->value());
        }
        else if(attributeName == "specularColor")
        {
            translucentColorMat->specularColor = ScanVector3f(a->value());
        }
        else if(attributeName == "translucencyColor")
        {
            translucentColorMat->translucentColor = ScanVector3f(a->value());
        }
        else if(attributeName == "shininess")
        {
            translucentColorMat->shininess = strtof(a->value(), 0);
        }
        else if(attributeName == "ambientIntensity")
        {
            translucentColorMat->ambientIntensity = strtof(a->value(), 0);
        }
        else if(attributeName == "translucentPower")
        {
            translucentColorMat->translucentPower = strtof(a->value(), 0);
        }
        else if(attributeName == "translucentScale")
        {
            translucentColorMat->translucentScale = strtof(a->value(), 0);
        }
        else if(attributeName == "translucentDistortion")
        {
            translucentColorMat->translucentDistortion = strtof(a->value(), 0);
        }
    }

    entityHandle.GetComponent<MeshInfo>().component->material = translucentColorMat;
}

void UnitySceneParser::ParseColorMaterial(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{

    ColorMaterial* colorMaterial;
    for (rapidxml::xml_attribute<> *a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute())
    {
        std::string attributeName = a->name();

        if (attributeName == "materialName")
        {
            std::string value(a->value());
            auto material = Game::Instance()->resourceManager->GetMaterial<ColorMaterial>(value);
            if(material == nullptr)
            {
                colorMaterial = Game::Instance()->resourceManager->CreateMaterial<ColorMaterial>(value);
            }
            else
            {
                colorMaterial = material;
            }

        }
        else if(attributeName == "mainColor")
        {
            colorMaterial->mainColor = ScanVector3f(a->value());
        }
        else if(attributeName == "specularColor")
        {
            colorMaterial->specularColor = ScanVector3f(a->value());
        }
        else if(attributeName == "shininess")
        {
            colorMaterial->shininess = strtof(a->value(), 0);
        }
        else if(attributeName == "ambientIntensity")
        {
            colorMaterial->ambientIntensity = strtof(a->value(), 0);
        }
    }
    entityHandle.GetComponent<MeshInfo>().component->material = colorMaterial;
}

void UnitySceneParser::ParseTextureMaterial(rapidxml::xml_node<> *node, EntityHandle entityHandle)
{
    TextureMaterial* textureMaterial;
    for (rapidxml::xml_attribute<> *a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute())
    {
        std::string attributeName = a->name();

        if (attributeName == "materialName")
        {
            std::string value(a->value());
            auto material = Game::Instance()->resourceManager->GetMaterial<TextureMaterial>(value);

            if(material == nullptr)
            {
                textureMaterial = Game::Instance()->resourceManager->CreateMaterial<TextureMaterial>(value);
            }
            else
            {
                textureMaterial = material;
            }

        }
        else if(attributeName == "diffuseTextureName")
        {
            std::string value(a->value());
            textureMaterial->diffuseTexture = Game::Instance()->resourceManager->GetTexture(value);
        }
        else if(attributeName == "specularTextureName")
        {
            std::string value(a->value());
            textureMaterial->specularTexture = Game::Instance()->resourceManager->GetTexture(value);
        }
        else if(attributeName == "emissionTextureName")
        {
            std::string value(a->value());
            textureMaterial->emissionTexture = Game::Instance()->resourceManager->GetTexture(value);
        }
        else if(attributeName == "mainColor")
        {
            textureMaterial->mainColor = ScanVector3f(a->value());
        }
        else if(attributeName == "specularColor")
        {
            textureMaterial->specularColor = ScanVector3f(a->value());
        }
        else if(attributeName == "shininess")
        {
            textureMaterial->shininess = strtof(a->value(), 0);
        }
        else if(attributeName == "ambientIntensity")
        {
            textureMaterial->ambientIntensity = strtof(a->value(), 0);
        }
        else if(attributeName == "emissionScale")
        {
            textureMaterial->emissionScale = strtof(a->value(), 0);
        }
    }

    entityHandle.GetComponent<MeshInfo>().component->material = textureMaterial;
}


glm::vec3 UnitySceneParser::ScanVector3f(const char *line)
{
    glm::vec3 vector = glm::vec3(0);
    int elementsScaned = sscanf(line, "(%f,%f,%f)", &vector.x, &vector.y, &vector.z);
    if(elementsScaned < 3)
    {
        ENGINE_LOG_ERROR("Parser could not scan vector3!");
        throw;
    }

    return vector;
}

glm::quat UnitySceneParser::ScanQuaternion(const char *charLine)
{
    glm::quat quaternion;
    int elementsScaned = sscanf(charLine, "(%f,%f,%f,%f)", &quaternion.x, &quaternion.y, &quaternion.z,&quaternion.w);
    if(elementsScaned < 4)
    {
        ENGINE_LOG_ERROR("Parser could not scan quaternion!");
        throw;
    }

    return quaternion;
}



