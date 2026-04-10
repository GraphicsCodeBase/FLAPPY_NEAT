#include "Window.h"
#include <iostream>

int main()
{
    Window window;
    if (!window.init(1280, 720, "FlappyNEAT"))
        return -1;

    std::cout << "Window opened successfully!\n";

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
