//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_FEATHER_H
#define CROW_FEATHER_H

#include "SystemManager.h"
#include "ComponentManager.h"
#include "EntityManager.h"


struct EntityHandle;

class Feather {

public:

    void Init();
    EntityHandle CreateEntity();
    void DestroyEntity(Entity entity);

    template <typename T>
    void RegisterComponent()
    {
        m_componentManager->RegisterComponent<T>();
    }

    template <typename T>
    void AddComponent(Entity entity,T component)
    {
        m_componentManager->AddComponent(entity,component);

        EntitySignature signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentType<T>(),true);
        m_entityManager->SetSignature(entity,signature);

        m_systemManager->OnEntitySignatureChanged(entity,signature);
    }

    template <typename T>
    void RemoveComponent(Entity entity)
    {
        m_componentManager->RemoveComponent<T>(entity);

        EntitySignature signature = m_entityManager->GetSignature(entity);
        signature.set(m_componentManager->GetComponentType<T>(),false);
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


    template <typename T>
    ComponentType GetComponentType()
    {
        return m_componentManager->GetComponentType<T>();
    }

    template <typename T>
    T* RegisterSystem()
    {
        T* system  =m_systemManager->RegisterSystem<T>();
        system->feather = this;
        return system;
    }

    template <typename T>
    void SetSystemSignature(EntitySignature signature)
    {
        m_systemManager->SetSignature<T>(signature);
    }

    template <typename T,typename... Args>
    void PopulateHandles(Entity e,ComponentHandle<T>& handle,ComponentHandle<Args> &... args)
    {
        ComponentArray<T>* array = m_componentManager->GetComponentArray<T>();
        handle = ComponentHandle<T>{e,array};
        PopulateHandles<Args...>(e,args...);
    }

    template <typename T>
    bool PopulateHandles(Entity e,ComponentHandle<T>& handle)
    {
        ComponentArray<T>* array = m_componentManager->GetComponentArray<T>();

        handle = ComponentHandle<T>{e, array};

        return array != nullptr;

    }

private:

    ComponentManager* m_componentManager;
    EntityManager* m_entityManager;
    SystemManager* m_systemManager;
};


#endif //CROW_FEATHER_H
