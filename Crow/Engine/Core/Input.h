//
// Created by Igli milaqi on 01/04/2020.
//

#ifndef CROW_INPUT_H
#define CROW_INPUT_H

#include <unordered_map>
#include "../Debug/Debug.h"


class Window;

///The input class wraps GLEW input detection in a more user friendly way.
///This input class works similar to Unity's way of detecting keyboard input.
///For now this class handles only keyboard input however mouse input will be added later.
class Input {

    friend class Window;

public:

    enum KeyState
    {
        PRESSED,
        ACTIVE,
        RELEASED
    };

    ///Checks if a key was pressed this frame.
    ///@param key The GLEW key that is being checked
    ///@return true if the key was pressed otherwise it will return false.
    static bool GetKeyDown(int key);

    ///Checks if a key is continuously being pressed
    ///@param key The GLEW key that is being checked
    ///@return true if the key is being pressed otherwise it will return false.
    static bool GetKey(int key);

    ///Checks if a key was released this frame.
    ///@param key The GLEW key that is being checked
    ///@return true if the key was released otherwise it will return false.
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
