#include "Window.h"
#include "Renderer.h"
#include "Game.h"
#include <algorithm>
#include <GLFW/glfw3.h>

int main()
{
    Window window;
    if (!window.init(Config::WINDOW_W, Config::WINDOW_H, "FlappyNEAT"))
        return -1;

    Renderer renderer;
    renderer.init();

    Game game(renderer);
    game.reset();

    // Capture start time AFTER init so the first frame dt is ~0, not init-load time.
    double prevTime = glfwGetTime();

    while (!window.shouldClose())
    {
        double now = glfwGetTime();
        float  dt  = static_cast<float>(now - prevTime);
        prevTime   = now;

        // Clamp dt: prevents a "spiral of death" if the window is dragged or
        // the OS stalls — without this, one huge dt causes dozens of physics
        // ticks at once and teleports birds into nonsensical positions.
        dt = std::min(dt, 0.1f);

        window.pollEvents();

        glClearColor(0.12f, 0.12f, 0.18f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.update(dt, window.handle());

        // Generation management lives here, not inside Game, so that Phase 2
        // NEAT can read final fitness scores and evolve before the reset.
        if (game.generationOver())
        {
            // TODO Phase 2: population.evolve(game.birds()) goes here
            game.reset();
        }

        window.swapBuffers();
    }

    renderer.shutdown();
    window.shutdown();
    return 0;
}
