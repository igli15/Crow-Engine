//
// Created by Igli milaqi on 15/03/2020.
//

#ifndef CROW_MESHRENDERERSYSTEM_H
#define CROW_MESHRENDERERSYSTEM_H

#include "../Feather/System.h"

class MeshRendererSystem : public System {


public:
    void Init() override;
    void Render() override;
};


#endif //CROW_MESHRENDERERSYSTEM_H
