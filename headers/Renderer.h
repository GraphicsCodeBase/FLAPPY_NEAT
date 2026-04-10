#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "Shaders.h"

struct Vertex {
    float x, y;        // position
    float r, g, b, a;  // color
};

class Renderer {
public:
    void init();
    void shutdown();

    void beginFrame();
    void endFrame();

    void drawQuad(float x, float y, float w, float h, float r, float g, float b, float a = 1.0f);
    void drawCircle(float cx, float cy, float radius, float r, float g, float b, float a = 1.0f, int segments = 16);

private:
    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;  // index buffer

    Shader m_shader;

    std::vector<Vertex>       m_vertices;
    std::vector<unsigned int> m_indices;
};
