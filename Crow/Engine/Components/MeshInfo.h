//
// Created by Igli milaqi on 14/03/2020.
//

#ifndef CROW_MESHINFO_H
#define CROW_MESHINFO_H

#include "../Rendering/Model.h"
#include "../Rendering/AbstractMaterial.h"
#include "../EventQueue/EventQueue.h"
#include "../Events/MeshInfoDirtyEvent.h"

struct MeshInfo {

    friend class MeshRendererSystem;

    MeshInfo(){};
    MeshInfo(Model* m,AbstractMaterial* mat)
    {
        SetModel(m);
        SetMaterial(mat);
    };

    void SetModel(Model* m)
    {
        model = m;

        if(owner!= InvalidEntity)
        EventQueue::Instance().Publish(new MeshInfoDirtyEvent(this));
    }

    void SetMaterial(AbstractMaterial* mat)
    {
        material = mat;

        if(owner!= InvalidEntity)
        EventQueue::Instance().Publish(new MeshInfoDirtyEvent(this));
    }

private:
    Model* model = nullptr;
    AbstractMaterial* material = nullptr;
    glm::mat4* modelMatrixPtr = nullptr;

    Entity owner = InvalidEntity;

};


#endif //CROW_MESHINFO_H
