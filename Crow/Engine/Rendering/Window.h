
//
// Created by Igli milaqi on 02/03/2020.
//

#ifndef CROW_WINDOW_H
#define CROW_WINDOW_H

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include "../Core/Input.h"

class Shader;
class Input;

class Window {

    friend class Input;

public:
    int CreateWindow(int windowWidth,int windowHeight,const char* windowName,int majorVersion = 3,int minorVersion = 3);
    bool isOpen();

    void ClearColor(float r,float g,float b,float a);
    void ProcessInput();
    void SwapBuffers();
    void PollEvents();
    void Terminate();
    void CloseWindow();
    void SetUpPostProcessingFrameBuffer(Shader* screenShader);
    inline static void InputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    unsigned int internalFrameBuffer = 0;
    unsigned int internalTextureColorBuffer = 0;
    unsigned int internalRBO = 0;

    unsigned int quadVAO;

private:

    GLFWwindow* m_internalWindow;

    void InternalInitGLEW();
    void GenerateScreenQuad();
    void GenerateFrameBuffer();
    void GenerateFrameBufferTexture();
    void GenerateFrameBufferRBO();

    unsigned int m_quadVBO;

};




#endif //CROW_WINDOW_H
