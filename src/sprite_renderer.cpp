#include "sprite_renderer.hpp"

#include <iostream>

// Vertex shader for sprite rendering
const char* spriteVertexShaderSource = R"(#version 300 es
    layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

    out vec2 TexCoords;

    uniform mat4 model;
    uniform mat4 projection;

    void main()
    {
        TexCoords = vertex.zw;
        gl_Position = projection * model * vec4(vertex.xy, 0.0, 1.0);
    }
)";

// Fragment shader for sprite rendering
const char* spriteFragmentShaderSource = R"(#version 300 es
    in vec2 TexCoords;
    out vec4 FragColor;

    uniform sampler2D image;
    uniform vec4 spriteColor;

    void main()
    {
        FragColor = spriteColor * texture(image, TexCoords); 
    }
)";

//-----
SpriteRenderer::SpriteRenderer() : mShaderProgram(0), mVAO(0), mVBO(0), mEBO(0)
{
}

//-----
SpriteRenderer::~SpriteRenderer()
{
    // unload textures

    if (mShaderProgram != 0)
    {
        glDeleteProgram(mShaderProgram);
    }

    if (mVAO != 0)
    {
        glDeleteVertexArrays(1, &mVAO);
    }

    if (mVBO != 0)
    {
        glDeleteBuffers(1, &mVBO);
    }

    if (mEBO != 0)
    {
        glDeleteBuffers(1, &mEBO);
    }
}

//-----
bool SpriteRenderer::initialize()
{
    bool compileSuccess =
        compileShaders(spriteVertexShaderSource, spriteFragmentShaderSource);
    if (!compileSuccess)
    {
        return false;
    }

    // Configure VAO VBO EBO
    float vertices[] = {
        // positions - texture coordinates
        0.0f, 1.0f, 0.0f, 1.0f, // top left
        1.0f, 1.0f, 1.0f, 1.0f, // top right
        1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        0.0f, 0.0f, 0.0f, 0.0f, // bottom left
    };

    unsigned int indices[] = {
        0, 1,
        2, // first triangle
        2, 3,
        0 // second triangle
    };

    // Bind to VAO to store rendering data
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    glBindVertexArray(mVAO);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Position and texture coordinate attributes
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);                     // Unbind from VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);         // Unbind from VBO after VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind from EBO after VAO

    return true;
}

//-----
bool SpriteRenderer::compileShaders(const char* vertexShaderSource,
                                    const char* fragmentShaderSource)
{
    if (vertexShaderSource == nullptr)
    {
        std::cerr << "Failed to compile empty vertex shader" << std::endl;
        return false;
    }

    if (fragmentShaderSource == nullptr)
    {
        std::cerr << "Failed to compile empty fragment shader" << std::endl;
        return false;
    }

    // Compile vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  vertexShaderCompileSuccess = 0;
    char vertexShaderCompileInfoLog[512];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompileSuccess);
    if (vertexShaderCompileSuccess == 0)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, vertexShaderCompileInfoLog);
        std::cerr << "Failed to compile vertex shader: "
                  << vertexShaderCompileInfoLog << std::endl;
        return false;
    }

    // Compile fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    int  fragmentShaderCompileSuccess = 0;
    char fragmentShaderCompileInfoLog[512];

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS,
                  &fragmentShaderCompileSuccess);
    if (fragmentShaderCompileSuccess == 0)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL,
                           fragmentShaderCompileInfoLog);
        std::cerr << "Failed to compile fragment shader: "
                  << fragmentShaderCompileInfoLog << std::endl;
        return false;
    }

    // Create GL program and link shaders
    mShaderProgram = glCreateProgram();
    glAttachShader(mShaderProgram, vertexShader);
    glAttachShader(mShaderProgram, fragmentShader);
    glLinkProgram(mShaderProgram);

    int  shaderProgramLinkSuccess = 0;
    char shaderProgramLinkInfoLog[512];

    glGetShaderiv(mShaderProgram, GL_LINK_STATUS, &shaderProgramLinkSuccess);
    if (shaderProgramLinkSuccess == 0)
    {
        glGetShaderInfoLog(mShaderProgram, 512, NULL, shaderProgramLinkInfoLog);
        std::cerr << "Failed to link shader program: "
                  << shaderProgramLinkInfoLog << std::endl;
        return false;
    }

    // Delete compiled shaders now that they are linked
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}
