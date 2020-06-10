//
// Created by Igli milaqi on 08/06/2020.
//

#include "AudioListenerSystem.h"
#include "../Components/Transform.h"
#include "../Feather/World.h"

void AudioListenerSystem::OnCreate()
{
    System::OnCreate();

    EventQueue::Instance().Subscribe(this,&AudioListenerSystem::OnListenerAdded);
}


void AudioListenerSystem::OnListenerAdded(ComponentAddedEvent<AudioListener> *event)
{
    Transform* listenerTransform = world->GetComponentPtr<Transform>(event->entity);

    if(listenerTransform == nullptr)
    {
        ENGINE_LOG_CRITICAL("Audio listener requires transform component!");
        throw;
    }

    glm::mat4 listenerTransformationMatrix = listenerTransform->GetWorldTransform();
    glm::vec3 listenerUpDir = listenerTransformationMatrix[1];
    glm::vec3 listenerForwardDir = listenerTransformationMatrix[2];
    glm::vec3 listenerPos =listenerTransformationMatrix[3];

    sf::Listener::setGlobalVolume(event->component->globalVolume);

    sf::Listener::setUpVector(listenerUpDir.x, listenerUpDir.y, listenerUpDir.z);
    sf::Listener::setDirection(listenerForwardDir.x, listenerForwardDir.y, listenerForwardDir.z);
    sf::Listener::setPosition(listenerPos.x, listenerPos.y, listenerPos.z);

    ENGINE_LOG(event->component->globalVolume);
}

void AudioListenerSystem::Update(float dt)
{
    System::Update(dt);

    auto listenerEntities = world->EntitiesWith<AudioListener,Transform>();

    if(listenerEntities.size() > 1)
    {
        ENGINE_LOG_ERROR("There can only be 1 AudioListener per World");
        throw;
    }

    for (int i = 0; i < listenerEntities.size(); ++i)
    {
        Transform& listenerTransform = world->GetComponent<Transform>(listenerEntities[0]);
        AudioListener& listener = world->GetComponent<AudioListener>(listenerEntities[0]);

        if(!listener.isStatic)
        {
            glm::mat4 listenerTransformationMatrix = listenerTransform.GetWorldTransform();
            glm::vec3 listenerUpDir = listenerTransformationMatrix[1];
            glm::vec3 listenerForwardDir = listenerTransformationMatrix[2];
            glm::vec3 listenerPos = listenerTransformationMatrix[3];

            sf::Listener::setUpVector(listenerUpDir.x, listenerUpDir.y, listenerUpDir.z);
            sf::Listener::setDirection(listenerForwardDir.x, listenerForwardDir.y, listenerForwardDir.z);
            sf::Listener::setPosition(listenerPos.x, listenerPos.y, listenerPos.z);
        }
    }

}

