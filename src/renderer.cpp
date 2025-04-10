#include "renderer.hpp"

#include <iostream>

//-----
Renderer::Renderer()
    : mWindow(nullptr), mWindowHeight(800), mWindowWidth(800), mVAO(0), mVBO(0)
{
}

//-----
Renderer::~Renderer()
{
    if (mVAO != 0)
    {
        glDeleteVertexArrays(1, &mVAO);
    }

    if (mVBO != 0)
    {
        glDeleteBuffers(1, &mVBO);
    }

    if (mWindow != nullptr)
    {
        glfwDestroyWindow(mWindow);
    }

    glfwTerminate();
}

//-----
bool Renderer::initialize(int width, int height)
{
    mWindowWidth  = width;
    mWindowHeight = height;

    bool glfwInitialized = glfwInit();
    if (!glfwInitialized)
    {
        std::cerr << "Failed to initialized GLFW" << std::endl;
        return false;
    }

    // WebGL 2 corresponds to GLFW 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

    // Create the game window
    mWindow = glfwCreateWindow(width, height, "Fishing!", nullptr, nullptr);
    if (mWindow == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(mWindow);

    // Set the viewport
    glViewport(0, 0, width, height);

    return true;
}

//-----
void Renderer::beginFrame()
{
    glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//-----
void Renderer::endFrame()
{
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}
