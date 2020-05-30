//
// Created by Igli milaqi on 29/05/2020.
//

#ifndef CROW_POOLREGISTRY_H
#define CROW_POOLREGISTRY_H

#include <unordered_map>
#include "Pool.h"
#include "CustomTypeID.h"

struct PoolTypeDummy
{

};

using PoolIDGenerator = CustomTypeID<PoolTypeDummy>;

class PoolRegistry
{
    template<typename T>
    T* AllocatePool(size_t maxSize)
    {
        auto iterator = m_poolMap.find(PoolIDGenerator::index < T > );

        if (iterator == m_poolMap.end())
        {
            Pool<T> pool = new Pool<T>();
            pool.Allocate(maxSize);
            m_poolMap.insert(iterator, std::make_pair(PoolIDGenerator::index < T > , pool));
        } else{
            ENGINE_LOG_WARNING("Pool is already registered.... Skipping");
        }
    }

    template<typename T>
    T* GetPool()
    {
        return m_poolMap[PoolIDGenerator::index<T>];
    }

private:
    ///All the component set pointers
    std::unordered_map<int, IPool*> m_poolMap;

};



#endif //CROW_POOLREGISTRY_H
