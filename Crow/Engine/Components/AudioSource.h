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
}


#endif //CROW_AUDIOSOURCE_H
