//
// Created by Igli milaqi on 09/06/2020.
//

#ifndef CROW_AUDIOSOURCESYSTEM_H
#define CROW_AUDIOSOURCESYSTEM_H


#include "../Feather/System.h"
#include "../Events/ComponentAddedEvent.h"
#include "../Events/ComponentRemovedEvent.h"
#include "../Components/AudioSource.h"
#include "../Feather/Pool.h"
#include "../../Game/Events/WorldResetEvent.h"

class AudioSourceSystem : public System
{
public:
    void OnCreate() override;
    void Init() override;
    void Update(float dt) override;

    void OnAudioSourceAdded(ComponentAddedEvent<AudioSource>* event);
    void OnAudioSourceRemoved(ComponentRemovedEvent<AudioSource>* event);
    void OnWorldReset(WorldResetEvent* event);
private:
    Pool<sf::Sound> m_soundPool;
};


#endif //CROW_AUDIOSOURCESYSTEM_H
