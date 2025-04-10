#pragma once

#include <GLES3/gl3.h>

class SpriteRenderer
{
  public:
    /// @brief Create a new sprite renderer.
    SpriteRenderer();

    /// @brief Destruct the sprite renderer.
    ~SpriteRenderer();

    /// @brief Initialize the sprite renderer.
    ///        Will compile shaders and prepare the renderer's buffers.
    /// @return True if the initialization is successful; false otherwise.
    bool initialize();

  private:
    /// @brief Compiles the given vertex and fragment shader sources.
    /// @param vertexShaderSource   The vertex shader source.
    /// @param fragmentShaderSource The fragment shader source.
    /// @return True if the shaders were successfully compiled; false otherwise.
    bool compileShaders(const char* vertexShaderSource,
                        const char* fragmentShaderSource);

    /// @brief The shader program for rendering sprites.
    unsigned int mShaderProgram;

    /// @brief Vertex array.
    unsigned int mVAO;

    /// @brief Vertex buffer.
    unsigned int mVBO;

    /// @brief Element buffer.
    unsigned int mEBO;
};
