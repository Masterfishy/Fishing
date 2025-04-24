#include "texture_loader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <GLES3/gl3.h>
#include <cstring>
#include <iostream>

/// @brief Callback when a texture is downloaded from the server.
/// @param fetch The emscripten fetch request.
void downloadSucceeded(emscripten_fetch_t* fetch)
{
    std::cout << fetch->status << " Fetched " << fetch->url
              << " bytes: " << fetch->numBytes << " bytes successfully!"
              << std::endl;

    const unsigned char* data =
        reinterpret_cast<const unsigned char*>(fetch->data);
    TextureLoader* loader = reinterpret_cast<TextureLoader*>(fetch->userData);

    unsigned int texture = loader->generateTexture(data, fetch->numBytes);
    loader->resolveRequests(fetch->url, texture);

    emscripten_fetch_close(fetch);
}

/// @brief Callback when a texture fails to fetch.
/// @param fetch The emscripten fetch request.
void downloadFailed(emscripten_fetch_t* fetch)
{
    std::cout << fetch->status << " Fetching " << fetch->url << " failed :("
              << std::endl;

    emscripten_fetch_close(fetch);
}

//-----
TextureLoader::TextureLoader() : mLoadRequests()
{
}

//-----
void TextureLoader::loadTexture(const std::string&    filePath,
                                TextureLoaderCallback callback)
{
    const auto& requestsIter = mLoadRequests.find(filePath);
    if (requestsIter == mLoadRequests.end())
    {
        std::vector<TextureLoaderCallback> callbacks = {callback};

        mLoadRequests.emplace(filePath, callbacks);
    }
    else
    {
        requestsIter->second.push_back(callback);
    }

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);

    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess  = downloadSucceeded;
    attr.onerror    = downloadFailed;
    attr.userData   = this;

    emscripten_fetch(&attr, filePath.c_str());
}

//-----
unsigned int TextureLoader::generateTexture(const unsigned char*   data,
                                            unsigned long long int length)
{
    int width      = 0;
    int height     = 0;
    int components = 0;

    unsigned char* imageData =
        stbi_load_from_memory(data, length, &width, &height, &components, 0);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0); // Unbind from the texture
    stbi_image_free(imageData);      // Free the image data

    return texture;
}

//-----
void TextureLoader::resolveRequests(const std::string& url,
                                    unsigned int       texture)
{
    const auto& requestsIter = mLoadRequests.find(url);
    if (requestsIter == mLoadRequests.end())
    {
        return;
    }

    const std::vector<TextureLoaderCallback>& callbacks = requestsIter->second;
    for (const auto& callback : callbacks)
    {
        callback(url, texture);
    }
}
