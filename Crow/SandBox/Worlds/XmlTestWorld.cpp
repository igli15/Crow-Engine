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

    Load("TestScene.xml");
}
