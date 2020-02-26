//
// Created by Igli milaqi on 25/02/2020.
//

#include "Gameobject.h"

void Gameobject::Update()
{
    for (int i = 0; i < m_allComponents.size(); ++i)
    {
        m_allComponents[i]->Update();
    }
}
