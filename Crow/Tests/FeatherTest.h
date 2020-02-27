//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_FEATHERTEST_H
#define CROW_FEATHERTEST_H

#include "../Feather/Feather.h"
#include "../Feather/EntityHandle.h"


struct ECSRigidBody
{
    float x =0 ;
    float y = 0;
};

struct ECSGravity
{
    float gravityValue;
};

struct ECSPlayer
{
    float maxY;
};

class GravitySystem : public System
{
public:
    Feather* feather;

    void UpdateSystem()
    {
        for(Entity const& entity : m_entities)
        {
            feather->GetComponent<ECSGravity>(entity).gravityValue += 1;
        }
    }
};

class PlayerPhysicsSystem : public System
{
public:
    Feather* feather;

    void UpdateSystem()
    {
        for(Entity const& entity : m_entities)
        {
            if(feather->GetComponent<ECSRigidBody>(entity).y > feather->GetComponent<ECSPlayer>(entity).maxY)
            {
                feather->GetComponent<ECSGravity>(entity).gravityValue = 0;
            };
        }
    }
};

class FeatherTest {

public:
    PlayerPhysicsSystem* testSystem;
    GravitySystem* gravitySystem;

    Feather* feather;

    void Init()
    {
        feather = new Feather();

      feather->Init();

        feather->RegisterComponent<ECSPlayer>();
        feather->RegisterComponent<ECSRigidBody>();
        feather->RegisterComponent<ECSGravity>();

        testSystem = feather->RegisterSystem<PlayerPhysicsSystem>();
        gravitySystem =  feather->RegisterSystem<GravitySystem>();

        testSystem->feather = feather;
        gravitySystem->feather = feather;

        EntitySignature signature;
        signature.set(feather->GetComponentType<ECSRigidBody>());
        signature.set(feather->GetComponentType<ECSPlayer>());
        signature.set(feather->GetComponentType<ECSGravity>());

        EntitySignature signature2;
        signature2.set(feather->GetComponentType<ECSGravity>());

        feather->SetSystemSignature<PlayerPhysicsSystem>(signature);
        feather->SetSystemSignature<GravitySystem>(signature2);

        for (int i = 0; i < 10000; i++)
        {
            EntityHandle handle = feather->CreateEntity();
            handle.AddComponent(ECSPlayer{500});
            handle.AddComponent(ECSGravity{0.001});
            handle.AddComponent(ECSRigidBody {0,0});
        }

        //feather->DestroyEntity(e);

    }

    void Update()
    {
        testSystem->UpdateSystem();
        gravitySystem->UpdateSystem();
    }

};


#endif //CROW_FEATHERTEST_H
