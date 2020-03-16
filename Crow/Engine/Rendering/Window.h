
//
// Created by Igli milaqi on 02/03/2020.
//

#ifndef CROW_WINDOW_H
#define CROW_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {

private:
    GLFWwindow* m_internalWindow;
    void InternalInitGLEW();


public:
    int CreateWindow(int windowWidth,int windowHeight,const char* windowName,int majorVersion = 3,int minorVersion = 3);
    bool isOpen();

    void ClearColor(float r,float g,float b,float a);
    void ProcessInput();
    void SwapBuffers();
    void PollEvents();
    void Terminate();

};


#endif //CROW_WINDOW_H