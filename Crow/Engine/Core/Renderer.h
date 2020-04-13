//
// Created by Igli milaqi on 09/04/2020.
//

#ifndef CROW_RENDERER_H
#define CROW_RENDERER_H


#include <vector>
#include <unordered_map>
#include "../Rendering/AbstractMaterial.h"
#include "../Components/MeshInfo.h"

struct MeshInstancedData
{
    MeshInfo meshInfo;
    std::vector<glm::mat4>* modelMatrices;
};

class Renderer {

public:
        std::vector<AbstractMaterial*> allMaterials;
        std::vector<Shader*> allShaders;
        std::unordered_map<int,MeshInstancedData> meshInfoMap;
        std::unordered_map<int,AbstractMaterial*> materialMap;
};


#endif //CROW_RENDERER_H
