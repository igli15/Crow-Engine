#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-auto"

#include "Engine/Debug/Debug.h"




#include "Engine/Rendering/Window.h"

#include <iostream>
#include <time.h>
#include "Engine/Core/Game.h"
#include "Engine/Debug/Debug.h"
#include "SandBox/MyGame.h"



#include "Engine/Feather/World.h"
#include "Engine/Feather/EntityHandle.h"

struct Position
{
    float x = 0.0f;
    float y = 0.0f;
};

struct Gravity
{
    float gravityValue = 9.8f;
};

class GravitySystem : public System
{
    void Update(float dt) override
    {
        world->ForEach<Position, Gravity>([&](Entity e, Position &position, Gravity &gravity) {
            position.y += gravity.gravityValue * dt;
        });

        std::vector<Entity> entities = world->FindEntities<Position>([&](Entity e, Position &position) {
            return (position.x == 0 && position.y == 0);
        });

        for (Entity e : entities)
        {
            world->DestroyEntity(e);
        }
    }

};

int main()
{
    Debug::Init();

    ComponentRegistry* componentRegistry = new ComponentRegistry();
    SystemRegistry* systemRegistry = new SystemRegistry();
    EntityRegistry* entityRegistry = new EntityRegistry();

    World* world = new World();
    world->Init(systemRegistry,entityRegistry,componentRegistry);


    componentRegistry->AllocateComponentSet<Position>();
    componentRegistry->AllocateComponentSet<Gravity>();

    systemRegistry->AllocateSystem<GravitySystem>();

    world->RegisterSystem<GravitySystem>();

    world->SetSystemSignature<GravitySystem,Position,Gravity>();

    EntityHandle entity = world->CreateEntity();

    entity.AddComponent<Position>(Position{0.0f,0.0f});
    entity.AddComponent<Gravity>(Gravity{9.18f});


    world->UpdateAllSystems(0.01f);


    //Debug::Log("Init Crow");

    /*
    Debug::Init();

    MyGame game;
    game.Init();
    game.LoadAssets();
    game.AllocateMemory();
    game.InitWorld();
    game.Run();
*/
    return 0;
}


#pragma clang diagnostic pop