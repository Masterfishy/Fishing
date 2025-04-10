#include "texture_loader.hpp"

#include <cstring>
#include <iostream>

/// @brief Callback when a texture is downloaded from the server.
/// @param fetch The emscripten fetch request.
void downloadSucceeded(emscripten_fetch_t* fetch)
{
    std::cout << fetch->status << " Fetched " << fetch->numBytes
              << " bytes successfully!" << std::endl;
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
TextureLoader::TextureLoader() : mLoadCallback(nullptr)
{
}

//-----
void TextureLoader::loadTexture(const std::string& name,
                                const std::string& filePath)
{
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);

    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess  = downloadSucceeded;
    attr.onerror    = downloadFailed;

    emscripten_fetch(&attr, filePath.c_str());
}
