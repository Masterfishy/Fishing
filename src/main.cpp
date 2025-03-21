// Game includes
#include "game.hpp"
#include "renderer.hpp"

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

/// @brief The game loop exposed to the browser.
void gameLoop()
{
    // Calculate the elapsed time
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime = std::chrono::duration<float>(currentTime - gLastFrameTime).count();
    gLastFrameTime = currentTime;

    // Update and render the game
    gGame->update(deltaTime);
    gGame->render();
}

/// @brief Entry point for the game program.
int main()
{
    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    gGame = std::make_unique<Game>(renderer);

    gLastFrameTime = std::chrono::high_resolution_clock::now();

    emscripten_set_main_loop(gameLoop, 0, false);

    return 0;
}
