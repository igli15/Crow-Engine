//
// Created by Igli milaqi on 14/03/2020.
//

#include "AbstractMaterial.h"
#include "../Core/Game.h"
#include "../Core/ResourceManager.h"

AbstractMaterial::AbstractMaterial(const std::string &shaderName)
{
    m_shader = (Game::Instance()->resourceManager->GetShader(shaderName));
}


Shader* AbstractMaterial::GetShader()
{
    return m_shader;
}
