cmake_minimum_required(VERSION 3.22)
project(Fishing)

# Enable C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch Packages
include(FetchContent)

# GLM
FetchContent_Declare(
    glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
	GIT_TAG 	    0af55ccecd98d4e5a8d1fad7de25ba429d60e863 #refs/1.0.1
)
FetchContent_MakeAvailable(glm)

# Emscripten specific configuration
if(EMSCRIPTEN)
    set(EMSCRIPTEN_LINK_FLAGS
        "-s WASM=1"
        "-s USE_WEBGL2=1"
        "-s FULL_ES3=1"
        "-s MIN_WEBGL_VERSION=2"
        "-s MAX_WEBGL_VERSION=2"
        "-s ALLOW_MEMORY_GROWTH=1"
        "-s NO_EXIT_RUNTIME=1"
        "-s EXPORTED_RUNTIME_METHODS=['ccall','cwrap']"
        "--bind"
        "-s USE_GLFW=3"
        # Optional flags for asset loading
        "-s ASYNCIFY=1"
        # Audio support
        "-s USE_SDL=2"
        "-s USE_SDL_MIXER=2"
        # Asset loading
        # "--preload-file assets"
    )
    string(JOIN " " EMSCRIPTEN_LINK_FLAGS_STR ${EMSCRIPTEN_LINK_FLAGS})
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EMSCRIPTEN_LINK_FLAGS_STR}")
    
    # Set output file extensions
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
endif()

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp
                               src/game.cpp
                               src/renderer.cpp
                               src/sprite_renderer.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm 
                                              glfw # from emscripten install
                                              )

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/components
)

# Output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Copy web files to bin
if(EMSCRIPTEN)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/web
            ${CMAKE_BINARY_DIR}/bin
    )
endif()
