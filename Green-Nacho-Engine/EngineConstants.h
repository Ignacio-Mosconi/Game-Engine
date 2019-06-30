#pragma once

// Shader Paths
constexpr const char* SIMPLE_VERTEX_SHADER_PATH = "Assets/Shaders/SimpleVertexShader.vertexshader";
constexpr const char* SIMPLE_PIXEL_SHADER_PATH = "Assets/Shaders/SimpleFragmentShader.fragmentshader";
constexpr const char* CUSTOM_VERTEX_SHADER_PATH = "Assets/Shaders/CustomVertexShader.vertexshader";
constexpr const char* CUSTOM_PIXEL_SHADER_PATH = "Assets/Shaders/CustomPixelShader.pixelshader";
constexpr const char* TEXTURE_VERTEX_SHADER_PATH = "Assets/Shaders/TextureVertexShader.vertexshader";
constexpr const char* TEXTURE_PIXEL_SHADER_PATH = "Assets/Shaders/TexturePixelShader.pixelshader";
constexpr const char* MODEL_TEX_VERTEX_SHADER_PATH = "Assets/Shaders/ModelTextureVertexShader.vertexshader";
constexpr const char* MODEL_TEX_PIXEL_SHADER_PATH = "Assets/Shaders/ModelTexturePixelShader.pixelshader";
// Vertex Buffer Properties
constexpr int VERTEX_COMPONENTS = 3;
constexpr int UV_COMPONENTS = 2;
// Primitives Vertices
constexpr int LINE_VERTICES = 2;
constexpr int TRIANGLE_VERTICES = 3;
constexpr int RECTANGLE_VERTICES = 4;
constexpr int CUBE_VERTICES = 8;
// Texture Loading
constexpr int BMP_HEADER_SIZE = 54;
// Level Loading
constexpr int LEVEL_LOAD_CHARS_BUFFER_SIZE = 64;
// Performance Properties
constexpr float DRAW_FRAME_TIME = 1.0f / 60.0f;
// Transform Properties
constexpr float FULL_ROTATION = 360.0f;