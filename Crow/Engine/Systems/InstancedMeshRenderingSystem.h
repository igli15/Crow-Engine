//
// Created by Igli milaqi on 04/04/2020.
//

#ifndef CROW_INSTANCEDMESHRENDERINGSYSTEM_H
#define CROW_INSTANCEDMESHRENDERINGSYSTEM_H


#include "../Feather/System.h"
#include "../Events/ComponentAddedEvent.h"
#include "../Components/InstancedMeshInfo.h"
#include "../Events/EntityEvents.h"
#include <unordered_map>
#include <vector>


struct InstancedModelData
{
    Model* model;
    std::vector<glm::mat4>* modelMatrices;
};
class Transform;
class Renderer;

class InstancedMeshRenderingSystem : public System{

public:
    void OnCreate() override;
    void Render() override;
    void OnMeshInfoAdded(ComponentAddedEvent<InstancedMeshInfo>* event);
    void OnEntityDestroyed(OnEntityDestroyedEvent* event);


private:
    std::unordered_map<int,std::vector<glm::mat4>> m_modelMap;
    std::unordered_map<int,InstancedModelData> m_instancedModelMap;

};


#endif //CROW_INSTANCEDMESHRENDERINGSYSTEM_H
