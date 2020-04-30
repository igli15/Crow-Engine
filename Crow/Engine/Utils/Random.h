//
// Created by Igli milaqi on 30/04/2020.
//

#ifndef CROW_RANDOM_H
#define CROW_RANDOM_H

#include <cstdlib>
#include <ctime>
#include "../Debug/Debug.h"

class Random
{
public:

    inline static void GenerateSeed(){ srand(time(nullptr)); };

    inline static int RandomRange(int min,int max) { return (rand() % max + min); };

    inline static float RandomRange(float min,float max)
    {
       if(max > min)
       {
           ENGINE_LOG_WARNING("max > min, returning min...");
           return min;
       }

        float random = ((float) rand()) / (float) RAND_MAX;
        float range = max - min;
        return (random*range) + min;
    };
};


#endif //CROW_RANDOM_H
