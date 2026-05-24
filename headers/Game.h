#pragma once
#include <vector>
#include <random>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Bird.h"
#include "Pipe.h"
#include "Renderer.h"
#include "config.h"

class Game {
public:
    explicit Game(Renderer& renderer);

    // Call once to initialise, and again after every generation ends.
    void reset();

    // Drive one wall-clock frame. Internally runs fixed-timestep ticks, then renders.
    void update(float dt, GLFWwindow* window);

    // True when every bird in the population is dead.
    bool generationOver() const;

    // Read-only access for Phase 2 NEAT — read fitness, bird state, pipe positions.
    const std::vector<Bird>& birds() const { return m_birds; }
    const std::vector<Pipe>& pipes() const { return m_pipes; }
    int generation() const { return m_generation; }

private:
    // --- Simulation ---
    void tick(GLFWwindow* window);
    void handleInput(GLFWwindow* window);   // Phase 1 spacebar only
    void spawnPipeIfDue();
    void updatePipes();
    void updateBirds();
    void awardPassFitness();
    void checkCollisions();
    void removeDeadPipes();

    // --- Rendering ---
    void render();
    void renderPipes();
    void renderBirds();

    Renderer&           m_renderer;
    std::vector<Bird>   m_birds;        // always POPULATION_SIZE elements
    std::vector<Pipe>   m_pipes;

    float               m_accumulator  = 0.0f;  // leftover wall-clock time
    float               m_pipeTimer    = 0.0f;  // counts up to PIPE_SPAWN_INTERVAL
    int                 m_generation   = 0;

    std::mt19937                          m_rng;
    std::uniform_real_distribution<float> m_gapDist;

    bool                m_spaceWasDown = false;  // debounce for spacebar
};
