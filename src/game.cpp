#include "game.hpp"

#include <iostream>

#include "renderer.hpp"

//-----
Game::Game(std::unique_ptr<Renderer> renderer) : mRenderer(std::move(renderer))
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
        std::cerr << "No renderer provided" << std::endl;
        return false;
    }

    bool rendererInitialized = mRenderer->initialize(width, height);
    if (!rendererInitialized)
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
}
