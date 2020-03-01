//
// Created by Igli milaqi on 25/02/2020.
//

#ifndef CROW_GAMEOBJECT_H
#define CROW_GAMEOBJECT_H

#include <vector>
#include <iostream>
#include "Component.h"

class OOPEngine;

class Gameobject {

private:
    std::vector<Component*> m_allComponents;


public:
    OOPEngine* engine;

    Gameobject()
    {

    }

    template <typename T>
    T* AddComponent()
    {
        T* component = new T();
        m_allComponents.push_back(component);
        component->parent = this;
        component->engine = engine;
        return component;
    }

    template <typename T>
    T* GetComponent()
    {

        for (int i = 0; i < m_allComponents.size(); i++)
        {
            if(dynamic_cast<T*>(m_allComponents[i]) != NULL)
            {
                return (T*)m_allComponents[i];
            }
        }

        //std::cout<<"GEtting Component"<<std::endl;
        return nullptr;
    }

    void StartAllComponents()
    {
        for (int i = 0; i < m_allComponents.size(); ++i)
        {
            m_allComponents[i]->Start();
        }
    }

    size_t GetComponentCount()
    {
        return  m_allComponents.size();
    }

    void Update();
};


#endif //CROW_GAMEOBJECT_H
