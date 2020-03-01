//
// Created by Igli milaqi on 16/02/2020.
//

#ifndef CROW_SYSTEM_H
#define CROW_SYSTEM_H

#include <set>
#include "Types.h"


class Feather;

class System {

public:
    Feather* feather;
    std::set<Entity> m_entities;

};


#endif //CROW_SYSTEM_H
