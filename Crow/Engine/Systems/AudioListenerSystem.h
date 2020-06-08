//
// Created by Igli milaqi on 08/06/2020.
//

#ifndef CROW_AUDIOLISTENERSYSTEM_H
#define CROW_AUDIOLISTENERSYSTEM_H


#include "../Feather/System.h"
#include "SFML/Audio.hpp"
#include "../Events/ComponentAddedEvent.h"
#include "../Components/AudioListener.h"

class AudioListenerSystem : public System
{
public:
    void OnListenerAdded(ComponentAddedEvent<AudioListener>* event);
    void Update(float dt) override;
};


#endif //CROW_AUDIOLISTENERSYSTEM_H
