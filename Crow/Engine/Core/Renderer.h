//
// Created by Igli milaqi on 09/04/2020.
//

#ifndef CROW_RENDERER_H
#define CROW_RENDERER_H


#include <vector>
#include "../Rendering/AbstractMaterial.h"

class Renderer {

public:
        std::vector<AbstractMaterial*> allMaterials;
        std::vector<Shader*> allShaders;
};


#endif //CROW_RENDERER_H
