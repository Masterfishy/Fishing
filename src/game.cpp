#include "game.hpp"

#include <iostream>

#include "renderer.hpp"

//-----
Game::Game(std::unique_ptr<Renderer> &renderer) : mRenderer(std::move(renderer))
{
}

//-----
Game::~Game()
{
}

//-----
void Game::update(float deltaTime)
{
    // std::cout << "A frame?!?!?!?!?" << std::endl;
}

//-----
void Game::render()
{
}
