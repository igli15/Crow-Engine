//
// Created by Igli milaqi on 02/03/2020.
//

#include <iostream>
#include "Window.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

int Window::CreateWindow(int windowWidth, int windowHeight, const char *windowName, int majorVersion, int minorVersion)
{
    //init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //only for apple
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //crate the glfw window
    m_internalWindow = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);

    //return 0 if the window failed to be created
    if (m_internalWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return 0;
    }

    //set the window as the current rendering context
    glfwMakeContextCurrent(m_internalWindow);
    //assign the callback needed
    glfwSetFramebufferSizeCallback(m_internalWindow,framebuffer_size_callback);

    //init GLEW
    InternalInitGLEW();


    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 1;
}

void Window::InternalInitGLEW()
{
    std::cout << "Initializing GLEW..." << std::endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
    std::cout << "Initialized GLEW, status (1 == OK, 0 == FAILED):" << (glewStatus == GLEW_OK) << std::endl << std::endl;
}

void Window::ProcessInput()
{
    if(glfwGetKey(m_internalWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_internalWindow, true);
    }
}

bool Window::isOpen()
{
    return !glfwWindowShouldClose(m_internalWindow);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_internalWindow);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::Terminate()
{
    glfwTerminate();
}

void Window::ClearColor(float r, float g, float b, float a)
{
    glClearColor(r, g,b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
