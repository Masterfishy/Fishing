#include "game.hpp"
#include "renderer.hpp"

//-----
Game::Game(std::unique_ptr<Renderer>& renderer)
  : mRenderer(std::move(renderer))
{}

//-----
Game::~Game() {}

//-----
void
Game::update(float deltaTime)
{}

//-----
void
Game::render()
{}
