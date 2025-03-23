#pragma once

#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

/// @brief A web renderer that uses OpenGL.
class Renderer
{
  public:
    /// @brief Construct a web renderer.
    Renderer();

    /// @brief Destruct the web renderer.
    ~Renderer();

    /// @brief Initialize the renderer and a window.
    bool initialize(int width, int height);

  private:
    /// The game window.
    GLFWwindow* mWindow;

    /// The height of the game window.
    int mWindowHeight;

    /// The width of the game window.
    int mWindowWidth;

    /// Vertex array.
    unsigned int mVAO;

    /// Vertex buffer.
    unsigned int mVBO;
};
