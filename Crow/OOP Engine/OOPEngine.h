//
// Created by Igli milaqi on 25/02/2020.
//

#ifndef CROW_NAIVEENGINE_H
#define CROW_NAIVEENGINE_H

#include <vector>
#include "Gameobject.h"

class OOPEngine {

private:

public:
    std::vector<Gameobject*> m_allGameobjects;

    template <typename T>
    T* CreateGameobject()
    {
        T* gameobject = new T();
        m_allGameobjects.push_back(gameobject);
        gameobject->engine = this;
        gameobject->AddComponents();
        return gameobject;
    }

    void StartAllGameObjects();
    void UpdateAllGameobjects();
};


#endif //CROW_NAIVEENGINE_H
