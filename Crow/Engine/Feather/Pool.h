//
// Created by Igli milaqi on 28/05/2020.
//

#ifndef CROW_POOL_H
#define CROW_POOL_H

#include <cstdlib>
#include "Types.h"


//TODO this works but, make sure you create a struct/union to make custom linked list for validIndexes so that we dont allocate another big array.
template<typename T>
class Pool
{

public:
    void Allocate(size_t maxSize)
    {
        m_dataArray = (T*)(calloc(maxSize, sizeof(T)));
        m_activeFlags = (bool*)(calloc(maxSize,sizeof(bool)));
        m_validIndexes = (int*)(calloc(maxSize,sizeof(int)));

    }

    size_t count = 0;

    T& GetNewData()
    {
         size_t currentCount = count;

         count++;

         if(m_validIndexesCount > 0)
         {
             if(m_emptyHoles>0) m_emptyHoles--;

             int index = m_validIndexes[m_validIndexesCount -1 ];
             m_validIndexesCount--;
             m_activeFlags[index] = true;
             return m_dataArray[index];

         } else
         {
             m_activeFlags[currentCount] = true;
             return m_dataArray[currentCount];
         }

    }

    void ReturnData(const T& data)
    {
        size_t index = GetIndexOfData(data);

        if(index <0 || index >= (count + m_emptyHoles))
        {
            ENGINE_LOG_CRITICAL("Bad Pool Access!");
            throw;
        }

        if(index != count + m_emptyHoles -1)
        {
            m_emptyHoles++;

            int vi = m_validIndexesCount;
            m_validIndexesCount++;
            m_validIndexes[vi] = index;
        }

        m_activeFlags[index] = false;

        count--;
    }

    void ForEach(typename std::common_type<std::function<void(T&)>>::type func)
    {
        ENGINE_LOG(m_emptyHoles);
        for (int i = 0; i < (count + m_emptyHoles); ++i)
        {
            if(m_activeFlags[i])
            {
                func(m_dataArray[i]);
            }
        }
    }

    size_t GetIndexOfData(const T& data)
    {
        return (&data - &m_dataArray[0]);
    }

private:


    unsigned int m_emptyHoles = 0;
    T* m_dataArray = nullptr;
    int* m_validIndexes = nullptr;
    size_t m_validIndexesCount = 0;
    bool* m_activeFlags = nullptr;
};

#endif //CROW_POOL_H
