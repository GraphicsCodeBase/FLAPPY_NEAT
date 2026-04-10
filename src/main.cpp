#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

int main()
{
    std::cout << "HELO WORLD !!!\n";
    std::cout << "Hello, FlappyNEAT!\n";

    // Verify GLFW initializes (confirms the library linked correctly)
    if (!glfwInit())
    {
        std::cerr << "GLFW init failed\n";
        return -1;
    }

    std::cout << "GLFW " << glfwGetVersionString() << " OK\n";
    std::cout << "GLM  " << GLM_VERSION_MAJOR << "."
                         << GLM_VERSION_MINOR << "."
                         << GLM_VERSION_PATCH << " OK\n";

    glfwTerminate();
    std::cout << "All dependencies loaded. Build is working!\n";
    return 0;
}
