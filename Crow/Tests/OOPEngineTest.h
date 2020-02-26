//
// Created by Igli milaqi on 25/02/2020.
//

#ifndef CROW_NAIVEENGINETEST_H
#define CROW_NAIVEENGINETEST_H

#endif //CROW_NAIVEENGINETEST_H

#include "../OOP Engine/OOPEngine.h"
#include "../OOP Engine/Component.h"

class RigidBody: public Component
{

public:

    float x =0 ;
    float y = 0;


};

class Gravity: public Component
{

private:
   RigidBody* rb;

public:
    float gravityValue = 10;

    void Start() override
    {
       // rb = parent->GetComponent<RigidBody>();
    }

    void Update() override
    {
        parent->GetComponent<RigidBody>()->y += gravityValue;
    }
};


class Player: public Component
{

public:
    //RigidBody* rb;
    //Gravity* gravity;

    void Start() override
    {
        //rb = parent->GetComponent<RigidBody>();
        //gravity = parent->GetComponent<Gravity>();
    }

    void Update() override
    {
        RigidBody* rb = parent->GetComponent<RigidBody>();
        Gravity* gravity = parent->GetComponent<Gravity>();

        if(rb!= nullptr && rb->y >= 500)
        {
            if(gravity != nullptr)
            gravity->gravityValue = 0;
        }
    }
};



class TestGameobject : public Gameobject
{
public:
    void AddComponents()
    {   AddComponent<RigidBody>();
        AddComponent<Player>();
       AddComponent<Gravity>();
    }
};


class OOPEngineTest
{

public:
    OOPEngine* engine;

    OOPEngineTest()
    {
        engine = new OOPEngine();

        for (int i = 0; i < 10000; ++i)
        {
            TestGameobject* gameobject = engine->CreateGameobject<TestGameobject>();
            gameobject->AddComponents();
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