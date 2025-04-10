#pragma once

// System includes
#include <memory>

///////////////////////////
// Forward declarations

class Renderer;
class SpriteRenderer;
class TextureLoader;

// end forward declarations
///////////////////////////

/// @brief A fishing game.
class Game
{
  public:
    /// @brief Construct a new fishing game.
    /// @param renderer The game's renderer.
    Game(std::unique_ptr<Renderer>       renderer,
         std::unique_ptr<SpriteRenderer> spriteRenderer,
         std::unique_ptr<TextureLoader>  textureLoader);

    /// @brief Shutdown the game.
    ~Game();

    /// @brief Initialize the game and all its systems.
    /// @param width  The width of the game window.
    /// @param height The height of the game window.
    bool initialize(int width, int height);

    /// @brief Update the game state with the given time step.
    /// @param deltaTime The amount of time elapsed since the last frame.
    void update(float deltaTime);

    /// @brief Render the game using the game's renderer.
    void render();

  private:
    /// @brief The renderer for the game.
    std::unique_ptr<Renderer> mRenderer;

    /// @brief The sprite renderer for the game.
    std::unique_ptr<SpriteRenderer> mSpriteRenderer;

    /// @brief The texture loader for the game.
    std::unique_ptr<TextureLoader> mTextureLoader;
};
