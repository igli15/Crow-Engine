//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_FEATHER_H
#define CROW_FEATHER_H

#include "SystemManager.h"
#include "ComponentManager.h"
#include "EntityManager.h"


struct EntityHandle;

class World {

public:

    virtual void Build();

    void Init();
    EntityHandle CreateEntity();
    void DestroyEntity(Entity entity);

    void InitAllSystems();
    void UpdateAllSystems();

    /*
    template <typename T>
    void RegisterComponent()
    {
        m_componentManager->RegisterComponent<T>();
    }
     */

    template <typename T>
    void AddComponent(Entity entity,T component)
    {
        m_componentManager->AddComponent(entity,component);
        EntitySignature signature = m_entityManager->GetSignature(entity);
        signature.set(ComponentIDGenerator::index<T>,true);
        m_entityManager->SetSignature(entity,signature);

        m_systemManager->OnEntitySignatureChanged(entity,signature);
    }

    template <typename T>
    void RemoveComponent(Entity entity)
    {
        m_componentManager->RemoveComponent<T>(entity);

        EntitySignature signature = m_entityManager->GetSignature(entity);
        signature.set(ComponentIDGenerator::index<T>,false);
        m_entityManager->SetSignature(entity,signature);

        m_systemManager->OnEntitySignatureChanged(entity,signature);
    }

    template <typename T>
    T& GetComponent(Entity entity)
    {
        return m_componentManager->GetComponent<T>(entity);
    }

    template <typename T>
    ComponentArray<T>* GetComponentArray()
    {
        return m_componentManager->GetComponentArray<T>();
    }


    /*
    template <typename T>
    ComponentType GetComponentType()
    {
        return m_componentManager->GetComponentType<T>();
    }
     */

    template <typename T>
    T* RegisterSystem()
    {
        T* system  =m_systemManager->RegisterSystem<T>();
        system->feather = this;
        m_allRegisteredSystems.push_back(system);
        return system;
    }

    template <typename SystemType>
    void SetSystemSignature(EntitySignature signature)
    {
        m_systemManager->SetSignature<SystemType>(signature);
    }

    template <typename SystemType,typename ...ComponentTypes>
    void SetSystemSignature()
    {
        EntitySignature signature;
        CreateSignature<ComponentTypes...>(signature);
        m_systemManager->SetSignature<SystemType>(signature);
    }

    template <typename T,typename... Args>
    void PopulateHandles(Entity e,ComponentHandle<T>& handle,ComponentHandle<Args> &... args)
    {
        ComponentArray<T>* array = m_componentManager->GetComponentArray<T>();
        handle = ComponentHandle<T>{e,array};
        PopulateHandles<Args...>(e,args...);
    }

    template <typename T>
    void PopulateHandles(Entity e,ComponentHandle<T>& handle)
    {
        ComponentArray<T>* array = m_componentManager->GetComponentArray<T>();

        handle = ComponentHandle<T>{e, array};

    }

    template<typename T,typename T2,typename ...Arg>
    void CreateSignature(EntitySignature& signature)
    {
        //https://stackoverflow.com/questions/27682042/why-is-this-variadic-function-call-ambiguous
        //we need 2 typenames before the template pack since when the pack is empty it becomes ambiguous with the Base Case.

        signature.set(ComponentIDGenerator::index<T>);
        CreateSignature<T2,Arg...>(signature);
    }

    //Base Case
    template <typename T>
    void CreateSignature(EntitySignature& signature)
    {
        signature.set(ComponentIDGenerator::index<T>);
    }

private:

    ComponentManager* m_componentManager;
    EntityManager* m_entityManager;
    SystemManager* m_systemManager;

    std::vector<System*> m_allRegisteredSystems;
};



#endif //CROW_FEATHER_H
