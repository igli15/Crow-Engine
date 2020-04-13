//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_MESHINFO_H
#define CROW_MESHINFO_H

#include "../Rendering/Model.h"
#include "../Rendering/AbstractMaterial.h"
#include "../EventQueue/EventQueue.h"
#include "../Events/MaterialAddedEvent.h"

struct MeshInfo {

    Model* model = nullptr;
    AbstractMaterial* material = nullptr;

};


#endif //CROW_MESHINFO_H
