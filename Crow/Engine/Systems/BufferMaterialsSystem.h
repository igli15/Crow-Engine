//
// Created by Igli milaqi on 10/04/2020.
//

#ifndef CROW_BUFFERMATERIALSSYSTEM_H
#define CROW_BUFFERMATERIALSSYSTEM_H


#include "../Feather/System.h"
#include "../Components/SpriteInfo.h"
#include "../Components/MeshInfo.h"
#include "../Events/ComponentRemovedEvent.h"

class Renderer;

class BufferMaterialsSystem : public System {


public:
    void Init() override;
    void PreRender() override;
    void OnCreate() override;

private:

    Renderer* m_renderer;

    void OnSpriteInfoRemoved(ComponentRemovedEvent<SpriteInfo>* event);
    void OnMeshInfoRemoved(ComponentRemovedEvent<MeshInfo>* event);

};


#endif //CROW_BUFFERMATERIALSSYSTEM_H
