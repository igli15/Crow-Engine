//
// Created by Igli milaqi on 08/06/2020.
//

#ifndef CROW_AUDIOSOURCE_H
#define CROW_AUDIOSOURCE_H

#include "SFML/Audio.hpp"
#include "../Debug/Debug.h"
#include "Transform.h"
#include "../Feather/World.h"

struct AudioSource
{

public:
    float volume = 100;
    float pitch = 1;
    sf::Music* music;

    Entity owner = InvalidEntity;
    World* world = nullptr;

    bool loop = false;
    bool playOnInit = true;
    bool is3DSource = false;
    bool isStatic = false;

    void PlayMusic()
    {
        if(music == nullptr)
        {
            ENGINE_LOG_CRITICAL("Music is not set to audiosource!");
            throw;
        }

        music->setVolume(volume);
        music->setLoop(loop);
        music->setPitch(pitch);

        if(is3DSource)
        {
            music->setRelativeToListener(true);
        }

        music->play();
    }

    void PlayOneShotSound(sf::Sound* sound)
    {
        sound->setVolume(volume);
        sound->setLoop(false);
        sound->setPitch(pitch);

        if(is3DSource)
        {
            sound->setRelativeToListener(true);
            Transform *ownerTransform = world->GetComponentPtr<Transform>(owner);
            if (ownerTransform == nullptr) {
                ENGINE_LOG_CRITICAL("Transform has to be attached to this audio source!");
                throw;
            }

            glm::vec3 ownerPos = ownerTransform->WorldPosition();
            sound->setPosition(ownerPos.x, ownerPos.y, ownerPos.z);
        }
        else
        {
            sound->setRelativeToListener(false);
        }

        sound->play();
    }


};


#endif //CROW_AUDIOSOURCE_H
