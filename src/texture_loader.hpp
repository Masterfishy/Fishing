#pragma once

#include <emscripten/fetch.h>
#include <functional>
#include <map>
#include <string>

using TextureLoaderCallback =
    std::function<void(const std::string&, unsigned int)>;

class TextureLoader
{
  public:
    TextureLoader();

    ~TextureLoader();

    /// @brief Load a texture from a file path asynchronously.
    /// @param url      The path of the texture to load.
    /// @param callback The function invoked once the texture is loaded.
    void loadTexture(const std::string& url, TextureLoaderCallback callback);

    /// @brief Load a texture from a file path asynchronously.
    /// @param url      The path of the texture to load.
    /// @param obj      The object to invoke the member function on.
    /// @param callback The function invoked once the texture is loaded.
    template <typename TObject>
    void loadTexture(const std::string& url, TObject* obj,
                     void (TObject::*callback)(const std::string&,
                                               unsigned int))
    {
        loadTexture(url, [=](const std::string& name, unsigned int texture) {
            (obj->*callback)(name, texture);
        });
    }

    /// @brief Generate a texture from the given raw image data.
    /// @param data   The raw image data as bytes.
    /// @param length The length of the data.
    /// @return A generated GL texture.
    unsigned int generateTexture(const unsigned char*   data,
                                 unsigned long long int length);

    /// @brief Add the given texture to the texture cache
    /// @param url      The url of the texture resource.
    /// @param texture  The generated GL texture for url.
    void cacheTexture(const std::string& url, unsigned int texture);

    /// @brief Resolve registered requests for resources with the given texture
    ///        data.
    /// @param url      The url of the requested resource.
    /// @param texture  The generated GL texture for the requested resource.
    void resolveRequests(const std::string& url, unsigned int texture);

  private:
    /// @brief The collection of texture requests.
    /// Key: Resource URL
    /// Value: List of callbacks
    std::map<std::string, std::vector<TextureLoaderCallback>> mLoadRequests;

    /// @brief A cache of all textures that have been generated from resource
    ///        requests.
    /// Key: Resource URL
    /// Value: GL Texture
    std::map<std::string, unsigned int> mTextureCache;
};
