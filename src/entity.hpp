#pragma once

#include "sprite.hpp"

class Entity
{
  public:
    Entity();

    ~Entity();

    Sprite& getSpriteComponent();

    Entity& setSpriteComponent(Sprite& component);

  private:
    Sprite mSpriteComponent;
};