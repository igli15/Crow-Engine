//
// Created by Igli milaqi on 31/03/2020.
//

#include "XmlTestWorld.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Editor/UnitySceneParser.h"
#include "../../Engine/Components/Light.h"
#include "../../Engine/Components/Transform.h"

void XmlTestWorld::Build()
{
    World::Build();

    UnitySceneParser::ParseUnityScene("TestScene.xml",this);

    Transform& lightTransform = GetComponent<Transform>(EntitiesWith<Light>()[0]);


    ENGINE_LOG(lightTransform.GetLocalTransform()[2].x);
    ENGINE_LOG(lightTransform.GetLocalTransform()[2].y);
    ENGINE_LOG(lightTransform.GetLocalTransform()[2].z);

}
