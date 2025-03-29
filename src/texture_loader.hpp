#pragma once

#include <emscripten/fetch.h>
#include <functional>
#include <string>

using TextureLoadCallback =
    std::function<void(unsigned int textureId, const std::string& name)>;

class TextureLoader
{
  public:
    TextureLoader();

    /// @brief Load a texture from a file path asynchronously.
    /// @param name     The name of the texture.
    /// @param filePath The path of the texture to load.
    void loadTexture(const std::string& name, const std::string& filePath);

  private:
    /// The callback triggered when a texture is loaded.
    TextureLoadCallback mLoadCallback;
};
