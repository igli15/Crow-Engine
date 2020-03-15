//
// Created by Igli milaqi on 15/03/2020.
//

#include "ColorMaterial.h"
#include "../Model.h"

void ColorMaterial::Render(Model *pMeshRenderer, const glm::mat4 &pModelMatrix, const glm::mat4 &pViewMatrix, const glm::mat4 &pProjectionMatrix)
{
    m_shader->Use();

    m_shader->SetMat4("projection",pProjectionMatrix);
    m_shader->SetMat4("view",pViewMatrix);
    m_shader->SetMat4("model",pModelMatrix);

    pMeshRenderer->Draw(*m_shader);

}
