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


class Health : public Component
{
public:
    float health = 200;
};



class Fire : public Component
{
public:
    float counter = 2000;
    bool extinguished = false;

    void Update () override
    {
       counter --;
       if(counter <= 0)
       {
           extinguished = true;
       }
    }
};

class FireBullet : public Component
{
public:
    float damageOverTime = 2;
    bool spawnedFire = false;

    void Update () override
    {
        Health* h = parent->GetComponent<Health>();
        h->health -= damageOverTime;

        if(h != nullptr && h->health <= 0 && !spawnedFire)
        {
            Gameobject* obj = engine->CreateGameobject<Gameobject>();
            obj->AddComponent<Transform>();
            obj->AddComponent<Fire>();
            spawnedFire = true;
        }
    }
};


class FireGun : public Component
{
public:

    float spawnTimer = 15;
    float counter = 0;
    void Update () override
    {
        counter += 10;

        if(counter >= spawnTimer)
        {
            counter = 0;
            Gameobject* obj = engine->CreateGameobject<Gameobject>();
            obj->AddComponent<Transform>();
            obj->AddComponent<Health>();
            obj->AddComponent<FireBullet>();
        }

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

        Gameobject* firePlayer = engine->CreateGameobject<Gameobject>();
        firePlayer->AddComponent<Transform>();
        firePlayer->AddComponent<FireGun>();
    }

    void Update()
    {
        engine->UpdateAllGameobjects();
    }

};