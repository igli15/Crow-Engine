//
// Created by Igli milaqi on 31/03/2020.
//

#include "XmlTestWorld.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Components/Transform.h"
#include "../../Engine/Components/Light.h"

void XmlTestWorld::Build()
{
    XMLWorld::Build();

    EntityHandle lightEntity = CreateEntity();
    auto dirLightTransform = lightEntity.AddComponent(Transform{});
    dirLightTransform->Rotate(-45,glm::vec3(1,0,0));
    Light* dirLight = lightEntity.AddComponent(Light{glm::vec3(0.8,0.8,0.8)});
    dirLight->intensity = 0.5;

    Load("TestScene.xml");
}
