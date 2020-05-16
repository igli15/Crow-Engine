//
// Created by Igli milaqi on 16/05/2020.
//

#ifndef CROW_PATHSYSTEM_H
#define CROW_PATHSYSTEM_H


#include "../../Engine/Feather/System.h"

class TargetSeekedEvent;

class PathSystem : public System
{
public:
    void Init() override;

    void OnPathSeeked(TargetSeekedEvent* event);
};


#endif //CROW_PATHSYSTEM_H
