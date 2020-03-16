//
// Created by Igli milaqi on 15/03/2020.
//

#include "ColorMaterial.h"
#include "../Model.h"
#include "../../Debug/Debug.h"

void ColorMaterial::Render(Model *pModel, const glm::mat4 &pModelMatrix, const glm::mat4 &pViewMatrix, const glm::mat4 &pProjectionMatrix)
{
    m_shader->Use();

    m_shader->SetMat4("projection",pProjectionMatrix);
    m_shader->SetMat4("view",pViewMatrix);
    m_shader->SetMat4("model",pModelMatrix);

    pModel->Draw(*m_shader);
}
