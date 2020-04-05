//
// Created by Igli milaqi on 04/04/2020.
//

#ifndef CROW_INSTANCEDMESHINFO_H
#define CROW_INSTANCEDMESHINFO_H

#include <string>
#include "../Rendering/Model.h"
#include "../Rendering/AbstractMaterial.h"

struct InstancedMeshInfo {

    Model* model;
    AbstractMaterial* material;

};


#endif //CROW_INSTANCEDMESHINFO_H
