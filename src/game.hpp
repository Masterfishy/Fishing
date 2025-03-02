#pragma once

// System includes
#include <memory>

///////////////////
// Forward declarations

class Renderer;

// end
///////////////////

/// @brief A fishing game.
class Game
{
public:
  /// @brief Construct a new fishing game.
  /// @param renderer The game's renderer.
  Game(std::unique_ptr<Renderer>& renderer);

  /// @brief Shutdown the game.
  ~Game();

  /// @brief Update the game state with the given time step.
  /// @param deltaTime The amount of time elapsed since the last frame.
  void update(float deltaTime);

  /// @brief Render the game using the game's renderer.
  void render();

private:
  /// @brief The renderer for the game.
  std::unique_ptr<Renderer> mRenderer;
};
