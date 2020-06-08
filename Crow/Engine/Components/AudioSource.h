//
// Created by Igli milaqi on 08/06/2020.
//

#ifndef CROW_AUDIOSOURCE_H
#define CROW_AUDIOSOURCE_H

#include "SFML/Audio.hpp"
#include "../Debug/Debug.h"

struct AudioSource
{

public:
    float volume = 100;
    float pitch = 1;
    bool loop = false;
    bool playOnInit = true;

    void PlayMusic();

    void PlaySound(sf::Sound* sound);

private:
    sf::Music* music;
};

void AudioSource::PlayMusic()
{
    if(music == nullptr)
    {
        ENGINE_LOG_CRITICAL("Music is not set to audiosource!");
        throw;
    }

    music->setVolume(volume);
    music->setLoop(loop);
    music->setPitch(pitch);
    music->play();
}

void AudioSource::PlaySound(sf::Sound *sound)
{
    sound->setVolume(volume);
    sound->setLoop(loop);
    sound->setPitch(pitch);
    sound->play();
}


#endif //CROW_AUDIOSOURCE_H
