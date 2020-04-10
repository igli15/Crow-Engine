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

    void SetMaterial(AbstractMaterial* newMat)
    {
        if(material == newMat) return;

        if(material!= nullptr) material->activeInstanceCount -= 1;

        material = newMat;
        material->activeInstanceCount += 1;

    };

    AbstractMaterial* GetMaterial()
    {
        return material;
    };

private:
    AbstractMaterial* material = nullptr;

};


#endif //CROW_INSTANCEDMESHINFO_H
