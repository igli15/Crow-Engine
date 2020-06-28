//
// Created by Igli milaqi on 09/04/2020.
//

#ifndef CROW_RENDERER_H
#define CROW_RENDERER_H


#include <vector>
#include <unordered_map>
#include "../Rendering/AbstractMaterial.h"
#include "../Components/MeshInfo.h"



///The Renderer class for now just hold references to renderable objects in the scene.
///The actual rendering is done by the Rendering Systems.
///All of this data might move to the systems too eventually.
class Renderer {

public:
        std::vector<AbstractMaterial*> allMaterials;
        std::vector<Shader*> allShaders;
        std::unordered_map<int,AbstractMaterial*> materialMap;

};


#endif //CROW_RENDERER_H
