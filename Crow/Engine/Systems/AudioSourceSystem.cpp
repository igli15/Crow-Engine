//
// Created by Igli milaqi on 09/06/2020.
//

#include "AudioSourceSystem.h"
#include "../Components/Transform.h"
#include "../Feather/World.h"

void AudioSourceSystem::OnCreate()
{
    System::OnCreate();

    m_soundPool.Allocate(100);

    EventQueue::Instance().Subscribe(this, &AudioSourceSystem::OnAudioSourceAdded);
    EventQueue::Instance().Subscribe(this, &AudioSourceSystem::OnAudioSourceRemoved);
    //EventQueue::Instance().Subscribe(this, &AudioSourceSystem::OnWorldReset);
}

void AudioSourceSystem::Init()
{
    System::Init();

    world->ForEach<AudioSource, Transform>([&](Entity entity, AudioSource &audioSource, Transform &transform) {
        if (audioSource.playOnInit) {
            if (audioSource.is3DSource) {
                glm::vec3 ownerPos = transform.WorldPosition();
                audioSource.sound->setPosition(ownerPos.x, ownerPos.y, ownerPos.z);
            } else {
                audioSource.sound->setRelativeToListener(false);
            }

            audioSource.Play();
        }
    });
}

void AudioSourceSystem::Update(float dt)
{
    System::Update(dt);

    world->ForEach<AudioSource,Transform>([](Entity entity, AudioSource &audioSource, Transform &transform)
    {
        if (audioSource.playOnInit)
        {
            if(!audioSource.is3DSource || audioSource.isStatic) return;

            glm::vec3 ownerPos = transform.WorldPosition();
            audioSource.sound->setPosition(ownerPos.x, ownerPos.y, ownerPos.z);
        }
    });

}

void AudioSourceSystem::OnAudioSourceAdded(ComponentAddedEvent<AudioSource> *event)
{
    event->component->owner = event->entity;
    event->component->world = world;

    event->component->sound = &m_soundPool.GetNewData();
    new(event->component->sound) sf::Sound();
    event->component->sound->setBuffer(*event->component->buffer);

    if(event->component->playOnAdd)
    {
        event->component->Play();
    }

}

void AudioSourceSystem::OnAudioSourceRemoved(ComponentRemovedEvent<AudioSource> *event)
{
    event->component.sound->stop();

    if (event->component.sound != nullptr) {
        m_soundPool.ReturnData(*event->component.sound);
    }
}

/*
void AudioSourceSystem::OnWorldReset(WorldResetEvent *event)
{
    world->ForEach<AudioSource>([this](Entity e,AudioSource& audioSource)
    {
        audioSource.sound->stop();

        if (audioSource.sound != nullptr) {
            m_soundPool.ReturnData(*audioSource.sound);
        }
    });
}
 */
