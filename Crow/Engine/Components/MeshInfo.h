//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_MESHINFO_H
#define CROW_MESHINFO_H

#include "../Rendering/Model.h"
#include "../Rendering/AbstractMaterial.h"

struct MeshInfo {

    Model* model;

    MeshInfo()
    {
    };

    MeshInfo(Model* pModel,AbstractMaterial* pMat)
    {
        model = pModel;
        material = pMat;
    };

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


#endif //CROW_MESHINFO_H
