//
// Created by Igli milaqi on 25/02/2020.
//

#ifndef CROW_NAIVEENGINETEST_H
#define CROW_NAIVEENGINETEST_H

#endif //CROW_NAIVEENGINETEST_H

#include "../OOP Engine/OOPEngine.h"
#include "../OOP Engine/Component.h"

class Transform: public Component
{

public:

    float x =0 ;
    float y = 0;
};

class Health: public Component
{

public:
    float hp =100;
};

class Gravity : public Component
{
public:
    float gravityPull = 9.8f;
    Transform* t;

    void Start()
    {
        t = parent->GetComponent<Transform>();
    }

    void Update()
    {
        t->y += gravityPull;
    }

};

class AutoDestroy : public Component
{
public:
    float timeToDestroy = 200;
    bool isDestroyed = false;
    float counter = 0;

    void Update()
    {
        counter ++;

        if(counter >= 200 && !isDestroyed)
        {
            isDestroyed = true;
            parent->GetComponent<Health>()->hp = 0;
        }
    }

};

class Ball : public Gameobject
{
public:
    void AddComponents() override
    {
        AddComponent<Transform>();
        AddComponent<Gravity>();
    }
};

class Asteroid : public Gameobject
{
public:
    void AddComponents() override
    {
        AddComponent<Transform>();
        AddComponent<AutoDestroy>();
        AddComponent<Health>();
    }
};


class OOPEngineTest
{

public:
    OOPEngine* engine;

    OOPEngineTest()
    {
        engine = new OOPEngine();

        for (int i = 0; i < 5000; ++i)
        {
            Ball *ball = engine->CreateGameobject<Ball>();
            Asteroid* asteroid = engine->CreateGameobject<Asteroid>();
        }
    }

    void Init()
    {
        engine->StartAllGameObjects();

    }

    void Update()
    {
        engine->UpdateAllGameobjects();
    }

};