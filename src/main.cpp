#include "Window.h"
#include "Renderer.h"
#include <iostream>

int main()
{
    Window window;
    if (!window.init(1280, 720, "FlappyNEAT"))
        return -1;

    Renderer renderer;
    renderer.init();

    while (!window.shouldClose())
    {
        window.pollEvents();

        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        renderer.beginFrame();

        // Draw a rectangle - orange  (world space [0,1])
        renderer.drawQuad(0.1f, 0.2f, 0.3f, 0.5f, 1.0f, 0.5f, 0.0f);

        // Draw a circle - cyan
        renderer.drawCircle(0.7f, 0.5f, 0.1f, 0.0f, 0.8f, 1.0f);

        renderer.endFrame();

        window.swapBuffers();
    }

    renderer.shutdown();
    window.shutdown();
    return 0;
}
