//
// Created by Igli milaqi on 25/02/2020.
//

#include "OOPEngine.h"

void OOPEngine::UpdateAllGameobjects()
{
    for (int i = 0; i < m_allGameobjects.size(); ++i)
    {
        m_allGameobjects[i]->Update();
    }
}

void OOPEngine::StartAllGameObjects()
{
    for (int i = 0; i < m_allGameobjects.size(); ++i)
    {
        m_allGameobjects[i]->StartAllComponents();
    }
}
