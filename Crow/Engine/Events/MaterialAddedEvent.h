//
// Created by Igli milaqi on 12/04/2020.
//

#ifndef CROW_MATERIALADDEDEVENT_H
#define CROW_MATERIALADDEDEVENT_H

#include "../EventQueue/Event.h"
#include "../Rendering/AbstractMaterial.h"

class MaterialAddedEvent : public Event
{
public:
    MaterialAddedEvent(AbstractMaterial* pMat) : material(pMat)
    {

    };

    AbstractMaterial* material;

};


#endif //CROW_MATERIALADDEDEVENT_H
