//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_MESHINFO_H
#define CROW_MESHINFO_H

#include "../Rendering/Model.h"
#include "../Rendering/AbstractMaterial.h"

struct MeshInfo {

public:
    Model* model;
    AbstractMaterial* material;

};


#endif //CROW_MESHINFO_H
