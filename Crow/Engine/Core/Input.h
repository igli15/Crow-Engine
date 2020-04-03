//
// Created by Igli milaqi on 01/04/2020.
//

#ifndef CROW_INPUT_H
#define CROW_INPUT_H

#include <unordered_map>
#include "../Debug/Debug.h"


class Window;

class Input {

    friend class Window;

public:

    enum KeyState
    {
        PRESSED,
        ACTIVE,
        RELEASED
    };

    static bool GetKeyDown(int key);
    static bool GetKey(int key);
    static bool GetKeyUp(int key);

private:
    Input(){};
    inline static Input* instance;
    Window* window;
    std::unordered_map<int,KeyState> m_keyMap;

    int InternalGetKey(int key);
    bool InternalGetKeyDown(int key);
    bool InternalGetKeyUp(int key);
};


#endif //CROW_INPUT_H
