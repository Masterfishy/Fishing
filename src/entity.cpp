#include "entity.hpp"

//-----
Entity::Entity() : mSpriteComponent()
{
}

//-----
Entity::~Entity()
{
}

//-----
Sprite& Entity::getSpriteComponent()
{
    return mSpriteComponent;
}

//-----
Entity& Entity::setSpriteComponent(Sprite& component)
{
    mSpriteComponent = component;
    return *this;
}
