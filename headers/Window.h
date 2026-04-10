#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
public:
    bool init(int width, int height, const std::string& title);
    void pollEvents();
    void swapBuffers();
    void shutdown();

    bool shouldClose() const;
    GLFWwindow* handle() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
};
