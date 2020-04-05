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

class Transform;

class InstancedMeshRenderingSystem : public System{

public:
    void OnCreate() override;
    void Render() override;
    void OnMeshInfoAdded(ComponentAddedEvent<InstancedMeshInfo>* event);
    void OnEntityDestroyed(OnEntityDestroyedEvent* event);


private:
    std::unordered_map<int,std::vector<glm::mat4>> m_modelMap;

};


#endif //CROW_INSTANCEDMESHRENDERINGSYSTEM_H
