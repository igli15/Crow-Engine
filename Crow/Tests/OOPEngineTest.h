//
// Created by Igli milaqi on 25/02/2020.
//

#ifndef CROW_NAIVEENGINETEST_H
#define CROW_NAIVEENGINETEST_H

#endif //CROW_NAIVEENGINETEST_H

#include "../OOP Engine/OOPEngine.h"
#include "../OOP Engine/Component.h"


class Kingdom : public Component
{
public:
    float humanity = 0;
    float populationRate = 0;
    float nobility = 0;
    float money = 0;
    float evil = 0;

};

class Creature : public Component
{
public:
    Kingdom* kingdom;
    float timeSpan = 80;
    bool isAlive = true;
    float timeCounter = 0.1f;
    float populationIncreaseRate = 0.1f;

    virtual void Update()
    {
        timeSpan -= timeCounter;

        if(isAlive && timeSpan<=0)
        {
            Die();
            kingdom->populationRate += populationIncreaseRate;
        }
    }

    virtual void Die()
    {
        isAlive = false;
    }
};

class Human : public Creature
{
public:
    float humanity = 20;

    virtual void Update() override
    {
        Creature::Update();

        kingdom->humanity += humanity;
    }

    virtual void Die() override
    {
        Creature::Die();

        kingdom->humanity -= 5;
    }
};

class Noble : public Human
{

public:
    float nobilityIncrease = 0.01f;
    float moneyIncrease = 0.1f;
    virtual void Update() override
    {
        Human::Update();
        kingdom->nobility += nobilityIncrease;
        kingdom->money += moneyIncrease;
    }

    virtual void Die() override
    {
        Human::Die();
        kingdom->nobility -= 5;
    }

};

class Orc : public Creature
{
public:
    float evilRate = 0.01f;

    virtual void Update() override
    {
        Creature::Update();
        kingdom->evil += evilRate;
    }

    virtual void Die() override
    {
        Creature::Die();
        kingdom->evil -= 5;
    }
};

class OOPEngineTest
{

public:
    OOPEngine* engine;

    OOPEngineTest()
    {
        engine = new OOPEngine();
    }

    void Init()
    {
        engine->StartAllGameObjects();

        Gameobject* kingdomObject = engine->CreateGameobject<Gameobject>();
        Kingdom* kingdom = kingdomObject->AddComponent<Kingdom>();

        for (int i = 0; i < 1000; ++i)
        {
            Gameobject* orc = engine->CreateGameobject<Gameobject>();
            Orc* o = orc->AddComponent<Orc>();
            o->kingdom =kingdom;
        }

        for (int i = 0; i < 1000; ++i)
        {
            Gameobject* noble = engine->CreateGameobject<Gameobject>();
            Noble* n = noble->AddComponent<Noble>();
            n->kingdom =kingdom;
        }

    }

    void Update()
    {
        engine->UpdateAllGameobjects();
    }

};