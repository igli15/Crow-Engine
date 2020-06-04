//
// Created by Igli milaqi on 12/04/2020.
//

#ifndef CROW_MESHINFODIRTYEVENT_H
#define CROW_MESHINFODIRTYEVENT_H

#include "../EventQueue/Event.h"
#include "../Rendering/AbstractMaterial.h"

class MeshInfo;
class MeshInfoDirtyEvent : public Event
{
public:
    MeshInfoDirtyEvent(MeshInfo* pMeshInfo) : meshInfo(pMeshInfo)
    {

    };

    MeshInfo* meshInfo;

};


#endif //CROW_MESHINFODIRTYEVENT_H
