//
// Created by Igli milaqi on 06/02/2020.
//

#ifndef CROW_DEBUG_H
#define CROW_DEBUG_H


#include <string>
#include <iostream>

class Debug {

public:
    static void Log(const std::string& s);
    static void Log(int i);
    static void Log(float f);

    static void Assert(bool assertion,const std::string&);

};


#endif //CROW_DEBUG_H
