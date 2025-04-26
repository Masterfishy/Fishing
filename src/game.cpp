#include "game.hpp"
#include "renderer.hpp"
#include "sprite_renderer.hpp"
#include "texture_loader.hpp"

#include "entity.hpp"

#include <iostream>

//-----
Game::Game(std::unique_ptr<Renderer>       renderer,
           std::unique_ptr<SpriteRenderer> spriteRenderer,
           std::unique_ptr<TextureLoader>  textureLoader)
    : mRenderer(std::move(renderer)),
      mSpriteRenderer(std::move(spriteRenderer)),
      mTextureLoader(std::move(textureLoader))
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

    if (mTextureLoader == nullptr)
    {
        std::cerr << "Failed to initialize game, no texture loader provided"
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

    mTextureLoader->loadTexture("assets/textures/fish_sprite.png", this,
                                &Game::addTexture);

    mEntities.emplace_back(Entity());

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

    for (auto& entity : mEntities)
    {
        Sprite& sprite = entity.getSpriteComponent();

        sprite.position.x += static_cast<int>(sprite.position.x + 10.0f) % 600;
        sprite.position.y += static_cast<int>(sprite.position.y + 10.0f) % 800;

        sprite.size.x += static_cast<int>(sprite.size.x * 2.0f) % 20;
        sprite.size.y += static_cast<int>(sprite.size.y * 2.0f) % 20;
    }

    std::cout << "Game alive!" << std::endl;
    counter = 0;
}

//-----
void Game::render()
{
    if (!mRenderer)
    {
        return;
    }

    mRenderer->beginFrame();

    if (mSpriteRenderer)
    {
        for (auto& entity : mEntities)
        {
            mSpriteRenderer->drawEntity(entity);
        }
    }

    mRenderer->endFrame();
}

//-----
void Game::addTexture(const std::string& name, unsigned int texture)
{
    std::cout << "Game - Add texture for " << name << std::endl;
    for (auto& entity : mEntities)
    {
        Sprite& sprite   = entity.getSpriteComponent();
        sprite.textureId = texture;
    }
}
