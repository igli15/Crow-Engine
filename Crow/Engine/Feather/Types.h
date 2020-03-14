//
// Created by Igli milaqi on 14/02/2020.
//

#ifndef CROW_TYPES_H
#define CROW_TYPES_H

#include <bitset>
#include "CustomTypeID.h"

using Entity = std::uint32_t;

struct ComponentTypeDummy
{

};

using ComponentType = std::uint32_t;
using ComponentIDGenerator = CustomTypeID<ComponentTypeDummy>;

const int MAX_ENTITIES = 3000;
const int MAX_COMPONENTS = 32;
using EntitySignature = std::bitset<MAX_COMPONENTS>;

#endif //CROW_TYPES_H
