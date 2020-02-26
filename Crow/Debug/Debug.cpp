//
// Created by Igli milaqi on 06/02/2020.
//

#include "Debug.h"

void Debug::Log(const std::string& s)
{
    std::cout<<s<<std::endl;
}

void Debug::Log(int i)
{
    std::cout<<i<<std::endl;
}

void Debug::Log(float f)
{
    std::cout<<f<<std::endl;
}

void Debug::Assert(bool assertion, const std::string& msg)
{
    assert(assertion && msg.data());
}
