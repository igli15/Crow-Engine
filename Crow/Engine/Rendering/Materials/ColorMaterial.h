//
// Created by Igli milaqi on 15/03/2020.
//

#ifndef CROW_COLORMATERIAL_H
#define CROW_COLORMATERIAL_H

#include "../AbstractMaterial.h"

class ColorMaterial :public AbstractMaterial {

public:
    void Render(Model* meshRenderer, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;


};


#endif //CROW_COLORMATERIAL_H
