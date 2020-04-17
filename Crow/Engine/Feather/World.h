//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_FEATHER_H
#define CROW_FEATHER_H

#include "SystemManager.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "../EventQueue/EventQueue.h"
#include "../Events/ComponentAddedEvent.h"

struct EntityHandle;

///The world class communicates with all the ecs managers.
///The user calls world functions and the world will update all the managers accordingly.
///It wraps all the functionality of the ecs managers.
class World {

public:

    ///Build is where all the systems and entities should be constructed.
    virtual void Build();

    ///Initializes the world.
    void Init();

    ///Creates an entity and returns a entity handle.
    ///@return EntityHandle of the newly created entity.
    EntityHandle CreateEntity();

    ///Destroys the entity and notifies all the managers immediately.
    ///It should be used internally only!!
    void InternalDestroyEntity(Entity entity);

    ///Marks an Entity for destruction and will be cleaned up next frame.
    ///@param entity The entity which should be destroyed.
    void DestroyEntity(Entity entity);

    ///Clears all the entities which were marked for destruction.
    void ClearEntityGarbage();

    ///Calls "Init" on all the registered systems.
    void InitAllSystems();

    ///Calls "Update" on all the registered systems.
    void UpdateAllSystems();

    ///Calls "Render" on all the registered systems.
    void RenderAllSystems();

    ///Calls "PreRender" on all the registered systems.
    void PreRenderAllSystems();

    ///Adds a component to an entity.
    ///@param entity Entity which the component will be added to.
    ///@param component The component which is going to be added.
    ///@return Returns a pointer the the component.
    template <typename T>
    T* AddComponent(Entity entity,T component)
    {
        T* c = m_componentManager->AddComponent(entity,component);
        EntitySignature signature = m_entityManager->GetSignature(entity);
        signature.set(ComponentIDGenerator::index<T>,true);
        m_entityManager->SetSignature(entity,signature);

        m_systemManager->OnEntitySignatureChanged(entity,signature);

        EventQueue::Instance().Publish(new ComponentAddedEvent<T>(entity,c));

        return c;
    }

    ///Removes a component of type "T" from an entity.
    ///@param entity Entity which the component will removed added from.
    template <typename T>
    void RemoveComponent(Entity entity)
    {
        m_componentManager->RemoveComponent<T>(entity);

        EntitySignature signature = m_entityManager->GetSignature(entity);
        signature.set(ComponentIDGenerator::index<T>,false);
        m_entityManager->SetSignature(entity,signature);

        m_systemManager->OnEntitySignatureChanged(entity,signature);
    }

    ///Get a component of type "T" from an entity.
    ///@param entity Entity which contains the component.
    ///@return Returns a reference to the found component (throws an error if not found).
    template <typename T>
    T& GetComponent(Entity entity)
    {
        return m_componentManager->GetComponent<T>(entity);
    }

    ///Get a component array of type "T".
    ///@return returns a pointer to the component array. nullptr will be returned if it wasn't found.
    template <typename T>
    ComponentArray<T>* GetComponentArray()
    {
        return m_componentManager->GetComponentArray<T>();
    }


    ///Register a system of type "T".
    ///An Error will be thrown if the system is already registered!
    ///@return Returns a pointer to the registered system.
    template <typename T>
    T* RegisterSystem()
    {
        T* system  =m_systemManager->RegisterSystem<T>();
        system->world = this;
        m_allRegisteredSystems.push_back(system);
        system->OnCreate();

        return system;
    }

    ///Sets the signature of a system of type "T".
    ///@param signature The new signature.
    template <typename SystemType>
    void SetSystemSignature(EntitySignature signature)
    {
        m_systemManager->SetSignature<SystemType>(signature);
    }

    ///Set the signature of a system of type "T" in one line.
    ///e.g SetSystemSignature<TypeOfSystem,Component1,Component2....>();
    ///The first type template is the system type and the rest are component types based on which the signature will be updated.
    template <typename SystemType,typename ...ComponentTypes>
    void SetSystemSignature()
    {
        EntitySignature signature;
        CreateSignature<ComponentTypes...>(signature);
        m_systemManager->SetSignature<SystemType>(signature);
    }

    ///Populates all the ComponentHandles based on a given entity.
    ///e.g PopulateHandle(entity,ComponentHandle<Component1>,ComponentHandle<Component2>....);
    ///If the component wasn't found the handle will be filled with a nullptr component
    ///@param e Entity which the component will be searched from.
    ///@param args all the component handles which will be filled.
    template <typename T,typename... Args>
    void PopulateHandles(Entity e,ComponentHandle<T>& handle,ComponentHandle<Args> &... args)
    {
        ComponentArray<T>* array = m_componentManager->GetComponentArray<T>();
        handle = ComponentHandle<T>{e,array};
        PopulateHandles<Args...>(e,args...);
    }

    ///Populates a signle ComponentHandle based on a given entity.
    template <typename T>
    void PopulateHandles(Entity e,ComponentHandle<T>& handle)
    {
        ComponentArray<T>* array = m_componentManager->GetComponentArray<T>();

        handle = ComponentHandle<T>{e, array};

    }

    ///Creates a signature for a system of type "T" based on the specified component types in one line.
    ///e.g CreateSignature<SystemType,Component1,Component2,Component3....>();
    ///@param a reference to the signature which will be changed.
    template<typename T,typename T2,typename ...Arg>
    void CreateSignature(EntitySignature& signature)
    {
        //https://stackoverflow.com/questions/27682042/why-is-this-variadic-function-call-ambiguous
        //we need 2 typenames before the template pack since when the pack is empty it becomes ambiguous with the Base Case.

        signature.set(ComponentIDGenerator::index<T>);
        CreateSignature<T2,Arg...>(signature);
    }

    ///Creates a signature for a system of type "T" based on a component type;
    ///@param a reference to the signature which will be changed.
    template <typename T>
    void CreateSignature(EntitySignature& signature)
    {
        signature.set(ComponentIDGenerator::index<T>);
    }


    ///Queries for all entities which contain the specified component types in one line.
    ///EntitiesWith will get the smallest array from the specified component types and then search the rest of the arrays
    ///based on the entities of that array only.
    ///e.g EntitesWith<Transform,RigidBody...>();
    ///@return Returns a std::vector of Entities.
    template <typename ...Args>
    std::vector<Entity> EntitiesWith()
    {
        auto result = std::vector<Entity>{};

        IComponentArray* smallestArray = GetSmallestArray<Args...>(GetComponentArray<Args>()...);

        result = smallestArray->GetEntities();

        if constexpr (sizeof...(Args) > 1) {
            QueryNeededEntities<IComponentArray,IComponentArray,Args...>(GetComponentArray<Args>()..., result);
        }

        return result;
    }


    ///Returns the smallest array from the specified ComponentArrays.
    ///@param componentArrays The arrays which will be compared.
    ///@return A pointer to the base class of the smallest array.
    template <typename ...Args>
    IComponentArray* GetSmallestArray(ComponentArray<Args>*... componentArrays)
    {
        return std::min(
                {static_cast<IComponentArray*>(componentArrays)...},
                [](const auto* poolA, const auto* poolB) {return poolA->validSize < poolB->validSize;}
        );
    }

    ///Looks into a component array based on an entity list and updates it based on if it contains the entity or not.
    ///If it does it moves on and if not it removes it from the current list.
    ///@param componentArray The component array which will be searched for entities.
    ///@param currentList A reference to a list of entities which will be updated.
    template <typename T>
    void QueryNeededEntities(ComponentArray<T>* componentArray,std::vector<Entity>& currentList)
    {
        for (auto it = currentList.begin() ; it != currentList.end() ; it++)
        {
            if(!componentArray->ContainsEntity(*it))
            {
                //decrement the iterator so we can safely remove it while looping
                currentList.erase(it--);
            }
        }
    }

    template <typename T,typename T2,typename ...Args>
    void QueryNeededEntities(ComponentArray<Args>*... componentArrays,std::vector<Entity>& currentList)
    {
        auto x = {(QueryNeededEntities(componentArrays,currentList),0)...};
    }




private:

    ComponentManager* m_componentManager;
    EntityManager* m_entityManager;
    SystemManager* m_systemManager;

    std::vector<Entity> m_entityGarbage;

    std::vector<System*> m_allRegisteredSystems;

    void RegisterEngineSystems();
};



#endif //CROW_FEATHER_H
