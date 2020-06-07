//
// Created by Igli milaqi on 08/06/2020.
//

#include "AudioClip.h"
#include "../Debug/Debug.h"

void AudioClip::Load(const std::string& path)
{
    m_buffer = new sf::SoundBuffer();
    m_sound = new sf::Sound();

    if(!m_buffer->loadFromFile(path))
    {
        ENGINE_LOG_ERROR("Could not load audio file!");
        throw;
    }

    m_sound->setBuffer(*m_buffer);
}

void AudioClip::Play()
{
    m_sound->play();
}
