#include "sprite_renderer.hpp"

//-----
SpriteRenderer::SpriteRenderer() : mShaderProgram(0), mVAO(0), mVBO(0), mEBO(0)
{
}

//-----
SpriteRenderer::~SpriteRenderer()
{
    // unload textures

    if (mShaderProgram != 0)
    {
        glDeleteProgram(mShaderProgram);
    }

    if (mVAO != 0)
    {
        glDeleteVertexArrays(1, &mVAO);
    }

    if (mVBO != 0)
    {
        glDeleteBuffers(1, &mVBO);
    }

    if (mEBO != 0)
    {
        glDeleteBuffers(1, &mEBO);
    }
}