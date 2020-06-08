//
// Created by Igli milaqi on 09/06/2020.
//

#include "AudioSourceSystem.h"
#include "../Components/Transform.h"
#include "../Feather/World.h"

void AudioSourceSystem::OnCreate()
{
    System::OnCreate();

    EventQueue::Instance().Subscribe(this,&AudioSourceSystem::OnAudioSourceAdded);
    EventQueue::Instance().Subscribe(this,&AudioSourceSystem::OnAudioSourceRemoved);
}

void AudioSourceSystem::Init()
{
    System::Init();

   world->ForEach<AudioSource,Transform>([&](Entity entity,AudioSource& audioSource,Transform& transform)
   {
       if(audioSource.playOnInit)
       {
           if(audioSource.is3DSource)
           {
               glm::vec3 ownerPos = transform.WorldPosition();
               audioSource.music->setPosition(ownerPos.x, ownerPos.y, ownerPos.z);
           }
           else
           {
               audioSource.music->setRelativeToListener(false);
           }

           audioSource.PlayMusic();
       }
   });
}

void AudioSourceSystem::Update(float dt)
{
    System::Update(dt);
}

void AudioSourceSystem::OnAudioSourceAdded(ComponentAddedEvent<AudioSource> *event)
{
    event->component->owner = event->entity;
    event->component->world = world;
}

void AudioSourceSystem::OnAudioSourceRemoved(ComponentRemovedEvent<AudioSource> *event)
{
    event->component.music->stop();
}
