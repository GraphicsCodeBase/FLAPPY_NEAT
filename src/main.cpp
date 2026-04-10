#include "Window.h"
#include "Shaders.h"
#include <iostream>

int main()
{
    Window window;
    if (!window.init(1280, 720, "FlappyNEAT"))
        return -1;

    std::cout << "Window opened successfully!\n";

    //try to load shaders
    Shader shader; //make the shader object.
    if (!shader.load("assets/Shaders/quad.vert", "assets/Shaders/quad.frag")) {
        std::cerr << "Failed to load shaders!\n";
        window.shutdown();
        return -1;
    }
    std::cout << "Shaders compiled successfully!\n";

    // Render loop
    while (!window.shouldClose())
    {
        window.pollEvents();

        // Clear to a dark blue-grey background
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        window.swapBuffers();
    }

    window.shutdown();
    return 0;
}
