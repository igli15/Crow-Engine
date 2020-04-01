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
#include "../Rendering/Materials/ColorMaterial.h"
#include "../Components/Camera.h"
#include "../Components/Light.h"

void XMLWorld::Build() {
    World::Build();
}

void XMLWorld::Load(const std::string &sceneName) {
    std::ifstream myXml(SCENE_PATH + sceneName);
    std::vector<char> buffer((std::istreambuf_iterator<char>(myXml)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    rapidxml::xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    rapidxml::xml_node<> *rootNode = doc.first_node("root");

    std::cout << "PARSING LEVEL....." << std::endl;

    ParseAllEntities(rootNode, EntityHandle{}, true);
}

void XMLWorld::ParseAllEntities(rapidxml::xml_node<> *node, EntityHandle entity, bool isRoot)
{
    if (node == nullptr) {
        ENGINE_LOG_ERROR("XML Node is null!");
    }

    for (rapidxml::xml_node<> *currentObjectNode = node->first_node();
         currentObjectNode != nullptr; currentObjectNode = currentObjectNode->next_sibling())
    {
        if (strcmp(currentObjectNode->name(), "GameObject") == 0)
        {
            EntityHandle currentNode = ParseEntity(currentObjectNode);

            if (currentObjectNode->first_node()->next_sibling() != nullptr)
            {
                rapidxml::xml_node<> *childNode = currentObjectNode->first_node()->next_sibling();
                for (rapidxml::xml_node<> *com = childNode; com != nullptr; com = com->next_sibling())
                {
                    if (strcmp(com->name(), "GameObject") == 0)
                    {
                        EntityHandle child = ParseEntity(com);
                        Transform *childTransform = child.GetComponent<Transform>().component;
                        Transform *parentTransform = currentNode.GetComponent<Transform>().component;

                        childTransform->SetParent(parentTransform);
                    }
                }

            }
        }

    }
}

EntityHandle XMLWorld::ParseEntity(rapidxml::xml_node<> *node) {
    EntityHandle entity = CreateEntity();
    Transform *entityTransform = entity.AddComponent(Transform{});

    for (rapidxml::xml_attribute<> *a = node->first_attribute();
         a != nullptr;
         a = a->next_attribute()) {
        std::string attributeName = a->name();

        if (attributeName == "position") {
            glm::vec3 pos;
            //seperate the value into 3 floats anf buffer them to pos vector...
            sscanf(a->value(), "(%f,%f,%f)", &pos.x, &pos.y, &pos.z);
            entityTransform->SetLocalPosition(pos);
        } else if (attributeName == "rotation") {
            glm::quat rot;
            //seperate the value into 4 floats anf buffer them to quaternion...
            sscanf(a->value(), "(%f,%f,%f,%f)", &rot.x, &rot.y, &rot.z, &rot.w);
            //sscanf(a->value(), "(%f,%f,%f,%f)", &rot.y, &rot.x, &rot.w, &rot.z);
            entityTransform->Rotate(rot);
            //entityTransform->Rotate(glm::angle(rot),glm::axis(rot));
        } else if (attributeName == "scale") {
            glm::vec3 scale;
            //seperate the value into 3 floats anf buffer them to scale vector...
            sscanf(a->value(), "(%f,%f,%f)", &scale.x, &scale.y, &scale.z);
            entityTransform->Scale(scale);
        } else if (attributeName == "mesh") {
            Model *mesh = Game::Instance()->resourceManager->GetModel(a->value());
            entity.AddComponent(
                    MeshInfo{mesh, Game::Instance()->resourceManager->GetMaterial<ColorMaterial>("defaultMat")});
        }

    }
    
    if (strcmp(node->first_node()->name(), "Components") == 0) {
        rapidxml::xml_node<> *compNode = node->first_node();
        for (rapidxml::xml_node<> *com = compNode->first_node(); com != nullptr; com = com->next_sibling()) {
            ParseComponents(com, entity);
        }
    }

    return entity;
}

void XMLWorld::ParseComponents(rapidxml::xml_node<> *com, EntityHandle newNode)
{
    if (strcmp(com->name(), "Camera") == 0) {

        Camera *cam = newNode.AddComponent(Camera{});

        for (rapidxml::xml_attribute<> *a = com->first_attribute();
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
    } else if (strcmp(com->name(), "Light") == 0) {
        Light *light = newNode.AddComponent(Light{});

        for (rapidxml::xml_attribute<> *a = com->first_attribute();
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
            } else if (attributeName == "color") {
                glm::vec3 color;
                sscanf(a->value(), "(%f,%f,%f)", &color.x, &color.y, &color.z);
                light->color = color;
            } else if (attributeName == "intensity") {
                light->intensity = strtof(a->value(), 0);
            } else if (attributeName == "attenuationConstants") {
                glm::vec3 consts;
                sscanf(a->value(), "(%f,%f,%f)", &consts.x, &consts.y, &consts.z);
                light->constant = consts.x;
                light->linear = consts.y;
                light->quadratic = consts.z;
            } else if (attributeName == "cutoffAngle") {
                light->cutoff = strtof(a->value(), 0);
            } else if (attributeName == "outercutoffAngle") {
                light->outerCutoff = strtof(a->value(), 0);
            }

        }

    }
}
