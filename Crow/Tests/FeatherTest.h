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

struct ECSHealth
{
public:
    float hp;
};

struct ECSGravity
{
public:
    float gravityPull = 9.8f;
};

struct ECSAutoDestroy
{
public:
    float counter;
    float timeToDestroy = 200;
    bool isDestroyed = false;
};


class AutoDestrouctionSystem : public System
{
public:
    void Update()
    {
        ComponentHandle<ECSHealth> healthHandle;
        ComponentHandle<ECSAutoDestroy> autoDestroyHandle;

        for (Entity const& entity: m_entities)
        {
            feather->PopulateHandles(entity,healthHandle,autoDestroyHandle);

            autoDestroyHandle.component->counter++;
            if(autoDestroyHandle.component->counter++ >= autoDestroyHandle.component->timeToDestroy && !autoDestroyHandle.component->isDestroyed)
            {
                autoDestroyHandle.component->isDestroyed =true;
            }
        }
    }
};

class FeatherTest {

public:

    Feather* feather;
    AutoDestrouctionSystem* autoDestrouctionSystem;

    void Init()
    {
        feather = new Feather();

      feather->Init();

        feather->RegisterComponent<ECSTransform>();
        feather->RegisterComponent<ECSHealth>();
        feather->RegisterComponent<ECSAutoDestroy>();
        feather->RegisterComponent<ECSGravity>();

        autoDestrouctionSystem = feather->RegisterSystem<AutoDestrouctionSystem>();

        EntitySignature signature;
        feather->CreateSignature<ECSHealth,ECSAutoDestroy>(signature);
        //std::cout<<signature.count()<<std::endl;

        feather->SetSystemSignature<AutoDestrouctionSystem>(signature);

        //feather->DestroyEntity(spaceShip.entity);

        for (int i = 0; i < 5000; ++i)
        {
            EntityHandle entity = feather->CreateEntity();
            entity.AddComponent(ECSHealth{});
            entity.AddComponent(ECSAutoDestroy{});
        }

    }

    void Update()
    {
        autoDestrouctionSystem->Update();
    }

};


#endif //CROW_FEATHERTEST_H
