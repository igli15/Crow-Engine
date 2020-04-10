//
// Created by Igli milaqi on 29/03/2020.
//

#ifndef CROW_TRANSFORMHIEARCHYSYSTEM_H
#define CROW_TRANSFORMHIEARCHYSYSTEM_H


#include "../Feather/System.h"
#include "../Components/Transform.h"
#include "../Events/EntityEvents.h"
#include "../Events/ComponentAddedEvent.h"
#include "../Events/ComponentRemovedEvent.h"

class TransformHierarchySystem : public System{

public:

    void OnCreate() override;

    void OnComponentAdded(ComponentAddedEvent<Transform>* event);
    void OnTransformRemoved(ComponentRemovedEvent<Transform>* event);

};


#endif //CROW_TRANSFORMHIEARCHYSYSTEM_H
