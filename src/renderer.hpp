#pragma once

///////////////////////
// Forward declarations

struct Sprite;

// end
///////////////////////

/// @brief A web renderer that uses OpenGL.
class Renderer
{
  public:
    /// @brief Construct a sprite web renderer.
    Renderer();

    /// @brief Destruct the sprite web renderer.
    ~Renderer();

    /// @brief Draw the given sprite.
    /// @param sprite The sprite data to draw.
    void drawSprite(const Sprite &sprite);
};
