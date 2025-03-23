#pragma once

#include <GLES3/gl3.h>

class SpriteRenderer
{
  public:
    SpriteRenderer();

    ~SpriteRenderer();

  private:
    /// @brief The shader program for rendering sprites.
    unsigned int mShaderProgram;

    /// @brief Vertex array.
    unsigned int mVAO;

    /// @brief Vertex buffer.
    unsigned int mVBO;

    /// @brief Element buffer.
    unsigned int mEBO;
};
