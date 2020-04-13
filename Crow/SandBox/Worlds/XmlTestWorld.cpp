//
// Created by Igli milaqi on 31/03/2020.
//

#include "XmlTestWorld.h"
#include "../../Engine/Feather/EntityHandle.h"
#include "../../Engine/Feather/World.h"
#include "../../Engine/Editor/UnitySceneParser.h"

void XmlTestWorld::Build()
{
    World::Build();

    UnitySceneParser::ParseUnityScene("TestScene.xml",this);


}
