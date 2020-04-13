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
#include <set>
#include "../Components/MeshInfo.h"

/*
struct MeshInstancedData
{
    MeshInfo* meshInfo;
    std::vector<glm::mat4>* modelMatrices;
};
 */

struct MeshData
{
    Model* meshInfo;
    AbstractMaterial* material;

    bool operator==(const MeshData& other)
    {
        return material->ID == other.material->ID;
    }
};

class Transform;
class Renderer;

class MeshRendererSystem : public System{

public:
    void OnCreate() override;
    void Render() override;
private:
    std::unordered_map<int,std::set<Model*>> m_matIdToModelsMap;
    std::unordered_map<int,std::vector<glm::mat4>*> m_modelIDtoMatricesMap;


   std::set<AbstractMaterial*> m_activeMaterials;
    Renderer* renderer;

};


#endif //CROW_MESHRENDERERSYSTEM_H
