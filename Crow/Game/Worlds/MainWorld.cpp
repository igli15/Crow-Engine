//
// Created by Igli milaqi on 20/04/2020.
//

#include "MainWorld.h"
#include "../../Engine/Editor/UnitySceneParser.h"
#include "../../Engine/Components/Light.h"


void MainWorld::Build()
{
    World::Build();
    UnitySceneParser::ParseUnityScene("MainLevel.xml",this);

}
