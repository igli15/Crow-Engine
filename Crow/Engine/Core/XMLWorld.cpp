//
// Created by Igli milaqi on 30/03/2020.
//

#include "XMLWorld.h"
#include <fstream>
#include <streambuf>
#include "../../Crow.h"
#include "../../Plugins/RapidXML/rapidxml.hpp"
#include "../Feather/EntityHandle.h"
#include "../Components/Transform.h"
#include "Game.h"
#include "ResourceManager.h"
#include "../Components/MeshInfo.h"

void XMLWorld::Build()
{
    World::Build();
}

void XMLWorld::Load(const std::string &sceneName)
{
    std::ifstream myXml(SCENE_PATH + sceneName);
    std::vector<char> buffer((std::istreambuf_iterator<char>(myXml)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    rapidxml::xml_node<>* rootNode = doc.first_node("root");

    std::cout << "PARSING LEVEL....." << std::endl;

    ParseAllEntities(rootNode,EntityHandle{},true);
}

void XMLWorld::ParseAllEntities(rapidxml::xml_node<> *node, EntityHandle entity, bool isRoot)
{
    EntityHandle currentNode = entity;

    //if it read GameObject
    if (strcmp(node->name(), "GameObject") == 0)
    {
        EntityHandle newNode = ParseEntity(node);

        if(isRoot)
        {
            currentNode = newNode;
        }

        //ColorMaterial* defaultMat = dynamic_cast<ColorMaterial*>(AbstractGame::Instance()->GetResourceManager()->GetMaterial("whiteMat"));
        //newNode->setMaterial(defaultMat);

        /*
        if (strcmp(node->first_node()->name(), "Components") == 0)
        {
            rapidxml::xml_node<>* compNode = node->first_node();
            for (rapidxml::xml_node<>* com = compNode->first_node(); com != nullptr; com = com->next_sibling())
            {
                ParseComponents(com, newNode);
            }
        }
         */

        if(!isRoot) {
            Transform *currentTransform = currentNode.GetComponent<Transform>().component;
            Transform *newTransform = newNode.GetComponent<Transform>().component;

            newTransform->SetParent(currentTransform);

            currentNode = newNode;
        }
    }

    ParseChildren(node, currentNode);
}

EntityHandle XMLWorld::ParseEntity(rapidxml::xml_node<> *node)
{
   EntityHandle entity = CreateEntity();
   Transform* entityTransform = entity.AddComponent(Transform{});

    for (rapidxml::xml_attribute<>* a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute())
    {
        std::string attributeName = a->name();

        if (attributeName == "position")
        {
            glm::vec3 pos;
            //seperate the value into 3 floats anf buffer them to pos vector...
            sscanf(a->value(), "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
            entityTransform->SetLocalPosition(pos);
        }
        else if (attributeName == "rotation")
        {
            glm::quat rot;
            //seperate the value into 4 floats anf buffer them to quaternion...
            sscanf(a->value(), "(%f,%f,%f,%f)", &rot.x, &rot.y, &rot.z, &rot.w);
            entityTransform->Rotate(glm::angle(rot), glm::axis(rot));
        }
        else if (attributeName == "scale")
        {
            glm::vec3 scale;
            //seperate the value into 3 floats anf buffer them to scale vector...
            sscanf(a->value(), "(%f,%f,%f)", &scale.x, &scale.y, &scale.z);
            entityTransform->Scale(scale);
        }
        else if (attributeName == "mesh")
        {
            Model* mesh = Game::Instance()->resourceManager->GetModel(a->value());
            //entity.AddComponent(MeshInfo{mesh,});
        }
    }

    return entity;
}

void XMLWorld::ParseChildren(rapidxml::xml_node<> *node, EntityHandle entity)
{
    for (rapidxml::xml_node<>* child = node->first_node(); child != nullptr; child = child->next_sibling())
    {
        ParseAllEntities(child,entity);
    }
}
