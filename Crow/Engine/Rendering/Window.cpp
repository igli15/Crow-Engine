//
// Created by Igli milaqi on 02/03/2020.
//

#include <iostream>
#include "Window.h"
#include "../Core/Input.h"
#include "../Debug/Debug.h"
#include "../Rendering/Shader.h"

#include <unordered_map>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

}

int Window::CreateWindow(int windowWidth, int windowHeight, const char *windowName, int majorVersion, int minorVersion)
{
    //init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
//

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
    glEnable(GL_MULTISAMPLE);

    Input::instance = new Input();
    Input::instance->window = this;
    glfwSetKeyCallback(m_internalWindow,Window::InputKeyCallback);

    glewExperimental = GL_TRUE;

    return 1;
}

void Window::InternalInitGLEW()
{
    std::cout << "Initializing GLEW..." << std::endl;
    //initialize the opengl extension wrangler
    GLint glewStatus = glewInit();
    glGetError(); // need to check for error here cuz a bug in glew throws an error in opengl
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


void Window::InputKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::KeyState state;

    auto keyIterator = Input::instance->m_keyMap.find(key);

    if(action == GLFW_PRESS && keyIterator == Input::instance->m_keyMap.end())
    {
        state = Input::KeyState::PRESSED;
        Input::instance->m_keyMap.insert(keyIterator,std::make_pair(key,state));
    }
    if(action == GLFW_PRESS && keyIterator != Input::instance->m_keyMap.end() && keyIterator->second == Input::KeyState::RELEASED)
    {
        state = Input::KeyState::PRESSED;
        keyIterator->second = state;
    }
    else if(action == GLFW_RELEASE && keyIterator != Input::instance->m_keyMap.end())
    {
        state = Input::KeyState::RELEASED;
        keyIterator->second = state;
    }

}

void Window::SetUpPostProcessingFrameBuffer(Shader* screenShader)
{
    screenShader->Use();
   GenerateScreenQuad();
   GenerateFrameBuffer();
   GenerateFrameBufferTexture();
   GenerateFrameBufferRBO();

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        ENGINE_LOG_ERROR("Framebuffer is not complete!");
        throw;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


void Window::GenerateScreenQuad()
{
    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
    };

    // screen quad VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &m_quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);
}

void Window::GenerateFrameBuffer()
{
    glGenFramebuffers(1, &internalFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, internalFrameBuffer);
}

void Window::GenerateFrameBufferTexture()
{
    glGenTextures(1, &internalTextureColorBuffer);
    glBindTexture(GL_TEXTURE_2D, internalTextureColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, internalTextureColorBuffer, 0);
}

void Window::GenerateFrameBufferRBO()
{
    //Generate render buffer objects for the depth and stencil testing

    glGenRenderbuffers(1, &internalRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, internalRBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, internalRBO);
}

