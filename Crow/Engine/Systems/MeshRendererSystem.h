//
// Created by Igli milaqi on 04/04/2020.
//

#ifndef CROW_MESHRENDERERSYSTEM_H
#define CROW_MESHRENDERERSYSTEM_H


#include "../Feather/System.h"
#include "../Events/ComponentAddedEvent.h"
#include "../Events/EntityEvents.h"
#include <unordered_map>
#include <vector>
#include "../Components/MeshInfo.h"

struct MeshInstancedData
{
    Model* model;
    std::vector<glm::mat4>* modelMatrices;
};
class Transform;
class Renderer;

class MeshRendererSystem : public System{

public:
    void OnCreate() override;
    void Render() override;
    void OnMeshInfoAdded(ComponentAddedEvent<MeshInfo>* event);


private:
    std::unordered_map<int,MeshInstancedData> m_instancedModelMap;

};


#endif //CROW_MESHRENDERERSYSTEM_H
