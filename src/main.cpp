// Game includes
#include "game.hpp"
#include "renderer.hpp"
#include "sprite_renderer.hpp"
#include "texture_loader.hpp"

// Emscripten includes
#include <emscripten.h>
#include <emscripten/html5.h>

// Standard includes
#include <chrono>
#include <iostream>

// Game variables
std::unique_ptr<Game> gGame;

// Frame timing variables
std::chrono::time_point<std::chrono::high_resolution_clock> gLastFrameTime;

const int GAME_WINDOW_WIDTH  = 800;
const int GAME_WINDOW_HEIGHT = 600;

/// @brief The game loop exposed to the browser.
void gameLoop()
{
    // Calculate the elapsed time
    auto  currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime =
        std::chrono::duration<float>(currentTime - gLastFrameTime).count();
    gLastFrameTime = currentTime;

    // Update and render the game
    gGame->update(deltaTime);
    gGame->render();
}

/// @brief Entry point for the game program.
int main()
{
    std::unique_ptr<Renderer>       renderer = std::make_unique<Renderer>();
    std::unique_ptr<SpriteRenderer> spriteRenderer =
        std::make_unique<SpriteRenderer>();
    std::unique_ptr<TextureLoader> textureLoader =
        std::make_unique<TextureLoader>();
    gGame =
        std::make_unique<Game>(std::move(renderer), std::move(spriteRenderer),
                               std::move(textureLoader));

    bool gameInitialized = gGame->initialize(800, 600);
    if (!gameInitialized)
    {
        return 1;
    }

    gLastFrameTime = std::chrono::high_resolution_clock::now();

    emscripten_set_main_loop(gameLoop, 0, false);

    return 0;
}
