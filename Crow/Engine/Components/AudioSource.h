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
    float volume = 100.0f;
    float pitch = 1.0f;
    float minDistance = 1.0f;
    float attenuation = 1.0f;

    sf::Sound* sound = nullptr;
    sf::SoundBuffer* buffer = nullptr;

    Entity owner = InvalidEntity;
    World* world = nullptr;

    bool loop = false;
    bool playOnInit = true;
    bool playOnAdd = false;
    bool is3DSource = false;
    bool isStatic = false;

    void Play()
    {
        if(sound == nullptr)
        {
            ENGINE_LOG_CRITICAL("sound is not set to audiosource!");
            throw;
        }

        sound->setVolume(volume);
        sound->setLoop(loop);
        sound->setPitch(pitch);

        if(is3DSource)
        {
            sound->setRelativeToListener(true);
            sound->setAttenuation(attenuation);
            sound->setMinDistance(minDistance);
        }

        sound->play();
    }

    void PlayOneShotSound(sf::Sound* sound)
    {
        sound->setVolume(volume);
        sound->setLoop(false);
        sound->setPitch(pitch);

        if(is3DSource)
        {
            sound->setRelativeToListener(true);
            sound->setAttenuation(attenuation);
            sound->setMinDistance(minDistance);

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
