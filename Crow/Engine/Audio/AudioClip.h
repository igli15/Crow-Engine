//
// Created by Igli milaqi on 08/06/2020.
//

#ifndef CROW_AUDIOCLIP_H
#define CROW_AUDIOCLIP_H

#include "SFML/Audio.hpp"

class AudioClip
{

public:
    void Load(const std::string& path);
    void Play();

private:
    sf::SoundBuffer* m_buffer;
    sf::Sound* m_sound;
};


#endif //CROW_AUDIOCLIP_H
