//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_FEATHERTEST_H
#define CROW_FEATHERTEST_H

#include "../Feather/World.h"
#include "../Feather/EntityHandle.h"


struct ECSKingdom
{
    float humanity = 0;
    float populationRate = 0;
    float nobility = 0;
    float money = 0;
    float evil = 0;
};

struct ECSCreature
{
    float timeSpan = 80;
    bool isAlive = true;
    float timeCounter = 0.1f;
    float populationIncreaseRate = 0.1f;
};

struct ECSNoble
{
    float humanity = 20;
    float nobilityIncrease = 0.01f;
    float moneyIncrease = 0.1f;
};

struct ECSOrc
{
    float evilRate = 0.01f;
};


class CreatureSystem : public System
{
public:
    ECSKingdom* kingdom;

    std::vector<ComponentHandle<ECSCreature>> handleCache;

    void Init()override
    {
        for (auto const& entity : m_entities)
        {
            ComponentHandle<ECSCreature> creature;
            feather->PopulateHandles(entity,creature);
            handleCache.push_back(creature);
        }
    }

    void Update()override
    {
        for (auto const& handle : handleCache)
        {
            handle.component->timeSpan -=  handle.component->timeCounter;

            if(handle.component->isAlive &&  handle.component->timeSpan<=0)
            {
                handle.component->isAlive = false;
                kingdom->populationRate +=  handle.component->populationIncreaseRate;
            }
        }
    }
};

class NobleSystem : public System
{
public:
    ECSKingdom* kingdom;

    std::vector<ComponentHandle<ECSNoble>> nobleCache;
    std::vector<ComponentHandle<ECSCreature>> creatureCache;

    void Init() override
    {
        for (auto const& entity : m_entities)
        {
            ComponentHandle<ECSNoble> noble;
            ComponentHandle<ECSCreature> creature;
            feather->PopulateHandles(entity,noble,creature);
            nobleCache.push_back(noble);
            creatureCache.push_back(creature);
        }
    }

    void Update()override
    {
        for (int i = 0; i< m_entities.size() ; i++)
        {
            ComponentHandle<ECSNoble> noble = nobleCache[i];
            ComponentHandle<ECSCreature> creature = creatureCache[i];
            kingdom->nobility += noble.component->nobilityIncrease;
            kingdom->money += noble.component->moneyIncrease;
            kingdom->humanity += noble.component->humanity;

            if(!creature.component->isAlive)
            {
                //OnDeath
            }
        }
    }
};

class OrcSystem : public System
{
public:
    ECSKingdom* kingdom;

    std::vector<ComponentHandle<ECSOrc>> orcCache;
    std::vector<ComponentHandle<ECSCreature>> creatureCache;

    void Init()override
    {
        for (auto const& entity : m_entities)
        {
            ComponentHandle<ECSOrc> orc;
            ComponentHandle<ECSCreature> creature;
            feather->PopulateHandles(entity,orc,creature);
            orcCache.push_back(orc);
            creatureCache.push_back(creature);
        }
    }

    void Update()override
    {
        for (int i = 0; i< m_entities.size() ; i++)
        {
            ComponentHandle<ECSOrc> orc = orcCache[i];
            ComponentHandle<ECSCreature> creature = creatureCache[i];
            kingdom->evil += orc.component->evilRate;

            if(!creature.component->isAlive)
            {
                //OnDeath
            }
        }
    }
};

class FeatherTest {

public:

    World* feather;
    CreatureSystem* creatureSystem;
    NobleSystem* nobleSystem;
    OrcSystem* orcSystem;

    void Init()
    {
        feather = new World();

      feather->Init();

        feather->RegisterComponent<ECSCreature>();
        feather->RegisterComponent<ECSKingdom>();
        feather->RegisterComponent<ECSNoble>();
        feather->RegisterComponent<ECSOrc>();

        creatureSystem = feather->RegisterSystem<CreatureSystem>();
        nobleSystem = feather->RegisterSystem<NobleSystem>();
        orcSystem = feather->RegisterSystem<OrcSystem>();

        /*
        EntitySignature signature;
        feather->CreateSignature<ECSCreature>(signature);
        feather->SetSystemSignature<CreatureSystem>(signature);
         */

        /*
        EntitySignature noblesignature;
        feather->CreateSignature<ECSCreature,ECSNoble>(signature);
        feather->SetSystemSignature<NobleSystem>(noblesignature);
         */
/*
        EntitySignature orcSignature;
        feather->CreateSignature<ECSCreature,ECSOrc>(orcSignature);
        feather->SetSystemSignature<OrcSystem>(orcSignature);
        */

        feather->SetSystemSignature<NobleSystem,ECSCreature,ECSNoble>();
        feather->SetSystemSignature<CreatureSystem,ECSCreature>();
        feather->SetSystemSignature<OrcSystem,ECSCreature,ECSOrc>();

        EntityHandle kingdomEntity = feather->CreateEntity();

        kingdomEntity.AddComponent(ECSKingdom{});

        creatureSystem->kingdom = kingdomEntity.GetComponent<ECSKingdom>().component;
        nobleSystem->kingdom = kingdomEntity.GetComponent<ECSKingdom>().component;
        orcSystem->kingdom = kingdomEntity.GetComponent<ECSKingdom>().component;

        for (int i = 0; i < 100000; ++i)
        {
            EntityHandle entity = feather->CreateEntity();
            entity.AddComponent(ECSCreature{});
            entity.AddComponent(ECSNoble{});
        }

        for (int i = 0; i < 100000; ++i)
        {
            EntityHandle entity = feather->CreateEntity();
            entity.AddComponent(ECSCreature{});
            entity.AddComponent(ECSOrc{});
        }

        feather->InitAllSystems();
    }

    void Update()
    {
        feather->UpdateAllSystems();
    }

};


#endif //CROW_FEATHERTEST_H
