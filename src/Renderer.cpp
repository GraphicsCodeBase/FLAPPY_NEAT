#include "Renderer.h"
#include <cmath>
#include <iostream>

static const float PI = 3.14159265358979f;

void Renderer::init()
{
    // Load shaders
    m_shader.load("assets/Shaders/quad.vert", "assets/Shaders/quad.frag");

    // Create VAO, VBO, EBO
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // Reserve GPU memory upfront (10000 vertices, 30000 indices)
    // nullptr means we're just reserving space, not uploading data yet
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 10000, nullptr, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 30000, nullptr, GL_DYNAMIC_DRAW);

    // Tell OpenGL how to read position (location = 0 in shader)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, x));
    glEnableVertexAttribArray(0);

    // Tell OpenGL how to read color (location = 1 in shader)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, r));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Renderer::shutdown()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    m_shader.shutdown();
}

void Renderer::beginFrame()
{
    // Clear the CPU-side batch ready for this frame
    m_vertices.clear();
    m_indices.clear();
}

void Renderer::drawQuad(float x, float y, float w, float h,
    float r, float g, float b, float a)
{
    // Index offset - each quad adds 4 vertices
    unsigned int base = (unsigned int)m_vertices.size();

    // 4 corners of the rectangle
    m_vertices.push_back({ x,     y,     r, g, b, a }); // bottom-left
    m_vertices.push_back({ x + w, y,     r, g, b, a }); // bottom-right
    m_vertices.push_back({ x + w, y + h, r, g, b, a }); // top-right
    m_vertices.push_back({ x,     y + h, r, g, b, a }); // top-left

    // 2 triangles to make a quad (6 indices)
    m_indices.push_back(base + 0);
    m_indices.push_back(base + 1);
    m_indices.push_back(base + 2);
    m_indices.push_back(base + 2);
    m_indices.push_back(base + 3);
    m_indices.push_back(base + 0);
}

void Renderer::drawCircle(float cx, float cy, float radius,
    float r, float g, float b, float a, int segments)
{
    unsigned int base = (unsigned int)m_vertices.size();

    // Centre vertex
    m_vertices.push_back({ cx, cy, r, g, b, a });

    // Ring of vertices around the centre
    for (int i = 0; i <= segments; i++) {
        float angle = (float)i / (float)segments * 2.0f * PI;
        float vx = cx + cosf(angle) * radius;
        float vy = cy + sinf(angle) * radius;
        m_vertices.push_back({ vx, vy, r, g, b, a });
    }

    // Triangle fan from centre to each pair of ring vertices
    for (int i = 0; i < segments; i++) {
        m_indices.push_back(base);          // centre
        m_indices.push_back(base + i + 1);  // current ring vertex
        m_indices.push_back(base + i + 2);  // next ring vertex
    }
}

void Renderer::endFrame()
{
    if (m_indices.empty())
        return;

    m_shader.use();
    glBindVertexArray(m_VAO);

    // Upload this frame's vertices to the GPU
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0,
        m_vertices.size() * sizeof(Vertex),
        m_vertices.data());

    // Upload this frame's indices to the GPU
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0,
        m_indices.size() * sizeof(unsigned int),
        m_indices.data());

    // Draw everything in one call
    glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
