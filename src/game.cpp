#include "game.hpp"
#include "renderer.hpp"
#include "sprite_renderer.hpp"

#include <iostream>

//-----
Game::Game(std::unique_ptr<Renderer>       renderer,
           std::unique_ptr<SpriteRenderer> spriteRenderer)
    : mRenderer(std::move(renderer)), mSpriteRenderer(std::move(spriteRenderer))
{
}

//-----
Game::~Game()
{
}

//-----
bool Game::initialize(int width, int height)
{
    if (mRenderer == nullptr)
    {
        std::cerr << "Failed to initialize game, no renderer provided"
                  << std::endl;
        return false;
    }

    if (mSpriteRenderer == nullptr)
    {
        std::cerr << "Failed to initialize game, no sprite renderer provided"
                  << std::endl;
        return false;
    }

    bool rendererInitialized = mRenderer->initialize(width, height);
    if (!rendererInitialized)
    {
        return false;
    }

    bool spriteRendererInitialized = mSpriteRenderer->initialize();
    if (!spriteRendererInitialized)
    {
        return false;
    }

    return true;
}

//-----
void Game::update(float deltaTime)
{
    static float counter = 0;

    if (counter < 5)
    {
        counter += deltaTime;
        return;
    }

    std::cout << "Game alive!" << std::endl;
    counter = 0;
}

//-----
void Game::render()
{
    mRenderer->beginFrame();

    mRenderer->endFrame();
}
