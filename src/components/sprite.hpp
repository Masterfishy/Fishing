#pragma once

#include <glm/glm.hpp>

/// @brief The data related to a renderable image.
struct Sprite
{
    /// @brief OpenGL texture ID.
    unsigned int textureId;

    /// @brief Position in world space.
    glm::vec2 position;

    /// @brief Size of the sprite.
    glm::vec2 size;

    /// @brief Rotation of the sprite in degrees.
    float rotation;

    /// @brief The tint color of the sprite.
    glm::vec4 color;

    /// @brief Construct a new sprite.
    /// @param id         The OpenGL texture ID.
    /// @param position   The position in world space.
    /// @param size       The size of the sprite.
    /// @param rotation   The rotation in degrees.
    /// @param color      The tint color.
    Sprite(unsigned int id = 0, glm::vec2 position = glm::vec2(0.0f),
           glm::vec2 size = glm::vec2(1.0f), float rotation = 0.0f,
           glm::vec4 color = glm::vec4(1.0f))
        : textureId(id), position(position), size(size), rotation(rotation),
          color(color)
    {
    }
};
