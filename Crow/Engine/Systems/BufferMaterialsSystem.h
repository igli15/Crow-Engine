//
// Created by Igli milaqi on 10/04/2020.
//

#ifndef CROW_BUFFERMATERIALSSYSTEM_H
#define CROW_BUFFERMATERIALSSYSTEM_H


#include "../Feather/System.h"

class Renderer;

class BufferMaterialsSystem : public System {


public:
    void Init() override;
    void PreRender() override;

private:

    Renderer* m_renderer;
};


#endif //CROW_BUFFERMATERIALSSYSTEM_H
