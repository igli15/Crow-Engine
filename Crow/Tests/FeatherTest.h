//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_FEATHERTEST_H
#define CROW_FEATHERTEST_H

#include "../Feather/Feather.h"
#include "../Feather/EntityHandle.h"


struct ECSTransform
{
    float x =0 ;
    float y = 0;
};

struct ECSFire
{
public:
    float counter = 2000;
    bool extinguished = false;
};

struct ECSFireBullet
{
public:
    float damageOverTime = 2;
    bool spawnedFire = false;
};

struct ECSFireGun
{
    float spawnTimer = 15;
    float counter = 0;
};

struct ECSHealth
{
public:
    float health = 200;
};


class FireGunSystem : public System
{
public:

    void Update()
    {
        ComponentHandle<ECSFireGun> fireGunHandle;

        for (Entity const& entity : m_entities)
        {
            feather->PopulateHandles(entity,fireGunHandle);

            fireGunHandle.component->counter += 10;

            if(fireGunHandle.component->counter >= fireGunHandle.component->spawnTimer)
            {
                EntityHandle bullet = feather->CreateEntity();
                bullet.AddComponent(ECSFireBullet{});
                bullet.AddComponent(ECSHealth{});
            }
        }
    }
};

class FireBulletSystem : public System
{
public:

    void Update()
    {
        ComponentHandle<ECSFireBullet> fireBulletHandle;
        ComponentHandle<ECSHealth> healthHandle;

        for (Entity const& entity : m_entities)
        {
            feather->PopulateHandles(entity,fireBulletHandle,healthHandle);

            healthHandle.component->health -= fireBulletHandle.component->damageOverTime;

            if(healthHandle.component->health <=0 && !fireBulletHandle.component->spawnedFire)
            {
                EntityHandle fire = feather->CreateEntity();
                fire.AddComponent(ECSTransform{});
                fire.AddComponent(ECSFire{});
                fireBulletHandle.component->spawnedFire = true;
            }
        }
    }
};


class FeatherTest {

public:

    Feather* feather;
    FireGunSystem* fireGunSystem;
    FireBulletSystem* fireBulletSystem;

    void Init()
    {
        feather = new Feather();

      feather->Init();

        feather->RegisterComponent<ECSTransform>();
        feather->RegisterComponent<ECSFireGun>();
        feather->RegisterComponent<ECSFireBullet>();
        feather->RegisterComponent<ECSHealth>();
        feather->RegisterComponent<ECSFire>();

        EntitySignature fireGunSign;
        fireGunSign.set(feather->GetComponentType<ECSFireGun>());

        EntitySignature fireBulletSign;
        fireBulletSign.set(feather->GetComponentType<ECSHealth>());
        fireBulletSign.set(feather->GetComponentType<ECSFireBullet>());

        fireGunSystem = feather->RegisterSystem<FireGunSystem,ECSFireGun>();
        fireBulletSystem = feather->RegisterSystem<FireBulletSystem,ECSHealth,ECSFireBullet>();

       // feather->SetSystemSignature<FireGunSystem>(fireGunSign);
        //feather->SetSystemSignature<FireBulletSystem>(fireBulletSign);

        EntityHandle firePlayer = feather->CreateEntity();
        firePlayer.AddComponent(ECSFireGun{});

        //feather->DestroyEntity(spaceShip.entity);

    }

    void Update()
    {
        fireGunSystem->Update();
        fireBulletSystem->Update();
    }

};


#endif //CROW_FEATHERTEST_H
