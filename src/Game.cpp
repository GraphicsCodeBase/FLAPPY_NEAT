#include "Game.h"
#include <algorithm>

// ------------------------------------------------------------------ lifecycle

Game::Game(Renderer& renderer)
    : m_renderer(renderer)
    , m_rng(std::random_device{}())
    , m_gapDist(Config::PIPE_GAP_MIN_Y, Config::PIPE_GAP_MAX_Y)
{
    // Allocate all birds once — they are reset in-place every generation,
    // so NEAT can hold stable indices into this vector.
    m_birds.resize(Config::POPULATION_SIZE);
}

void Game::reset()
{
    for (auto& bird : m_birds)
        bird.reset();

    m_pipes.clear();
    m_accumulator  = 0.0f;
    m_pipeTimer    = 0.0f;
    m_spaceWasDown = false;
    ++m_generation;
}

// ------------------------------------------------------------------ public API

void Game::update(float dt, GLFWwindow* window)
{
    m_accumulator += dt;
    while (m_accumulator >= Config::FIXED_DT)
    {
        tick(window);
        m_accumulator -= Config::FIXED_DT;
    }
    render();
}

bool Game::generationOver() const
{
    for (const auto& bird : m_birds)
        if (bird.alive()) return false;
    return true;
}

// ------------------------------------------------------------------ simulation

void Game::tick(GLFWwindow* window)
{
    // Order matters — see CLAUDE.md for the full rationale.
    handleInput(window);    // 1. player input (Phase 1 only)
    spawnPipeIfDue();       // 2. emit a new pipe if the timer is up
    updatePipes();          // 3. move all pipes left
    updateBirds();          // 4. apply gravity / clamp speed / accumulate frame fitness
    awardPassFitness();     // 5. reward birds that cleared a pipe this tick
    checkCollisions();      // 6. kill birds that hit a pipe
    removeDeadPipes();      // 7. discard pipes that have scrolled off-screen
}

void Game::handleInput(GLFWwindow* window)
{
    // Phase 1 testing only: spacebar makes bird[0] flap.
    // Debounced so that holding the key fires once per press, not 60×/sec.
    // In Phase 2 this function is removed; each bird will be driven by its network.
    bool spaceDown = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    if (spaceDown && !m_spaceWasDown && m_birds[0].alive())
        m_birds[0].flap();
    m_spaceWasDown = spaceDown;
}

void Game::spawnPipeIfDue()
{
    m_pipeTimer += Config::FIXED_DT;
    if (m_pipeTimer >= Config::PIPE_SPAWN_INTERVAL)
    {
        m_pipeTimer -= Config::PIPE_SPAWN_INTERVAL;
        m_pipes.emplace_back(m_gapDist(m_rng));
    }
}

void Game::updateBirds()
{
    for (auto& bird : m_birds)
    {
        bird.update(Config::FIXED_DT);
        // Award survival fitness only if the bird is still alive after physics.
        // This correctly withholds the reward on the tick the bird dies.
        if (bird.alive())
            bird.addFitness(Config::FITNESS_FRAME_WEIGHT);
    }
}

void Game::updatePipes()
{
    for (auto& pipe : m_pipes)
        pipe.update(Config::FIXED_DT);
}

void Game::awardPassFitness()
{
    for (auto& pipe : m_pipes)
    {
        if (pipe.passed()) continue;

        // A pipe is passed when its right edge has cleared every alive bird's left edge.
        // We use the first alive bird as the reference (all share the same X=BIRD_X).
        for (const auto& bird : m_birds)
        {
            if (!bird.alive()) continue;

            if (pipe.x() + Config::PIPE_WIDTH < bird.x() - Config::BIRD_RADIUS)
            {
                // Mark before looping over birds so we don't re-enter this block.
                pipe.markPassed();
                for (auto& b : m_birds)
                    if (b.alive())
                        b.addFitness(Config::FITNESS_PIPE_WEIGHT);
            }
            break; // only need to check one alive bird for the X comparison
        }
    }
}

void Game::checkCollisions()
{
    for (auto& bird : m_birds)
    {
        if (!bird.alive()) continue;

        for (const auto& pipe : m_pipes)
        {
            // Use BIRD_HITBOX (smaller than visual radius) for a forgiving feel.
            // Fast reject: is the bird horizontally overlapping the pipe column?
            bool inColumn = bird.x() + Config::BIRD_HITBOX > pipe.x() &&
                            bird.x() - Config::BIRD_HITBOX < pipe.x() + Config::PIPE_WIDTH;
            if (!inColumn) continue;

            // The bird is in the column — is it outside the gap?
            bool hitsTop    = bird.y() + Config::BIRD_HITBOX > pipe.gapTop();
            bool hitsBottom = bird.y() - Config::BIRD_HITBOX < pipe.gapBottom();

            if (hitsTop || hitsBottom)
                bird.kill();
        }
    }
}

void Game::removeDeadPipes()
{
    // erase-remove idiom (C++17 compatible; std::erase_if needs C++20)
    m_pipes.erase(
        std::remove_if(m_pipes.begin(), m_pipes.end(),
            [](const Pipe& p) { return p.offScreen(); }),
        m_pipes.end()
    );
}

// ------------------------------------------------------------------ rendering

void Game::render()
{
    m_renderer.beginFrame();
    renderPipes();   // pipes first (background)
    renderBirds();   // birds on top
    m_renderer.endFrame();
}

void Game::renderPipes()
{
    for (const auto& pipe : m_pipes)
    {
        // Top pipe: rectangle from gapTop() up to Y=1.0
        m_renderer.drawQuad(
            pipe.x(), pipe.gapTop(),
            Config::PIPE_WIDTH, 1.0f - pipe.gapTop(),
            0.2f, 0.8f, 0.2f
        );

        // Bottom pipe: rectangle from Y=0.0 up to gapBottom()
        m_renderer.drawQuad(
            pipe.x(), 0.0f,
            Config::PIPE_WIDTH, pipe.gapBottom(),
            0.2f, 0.8f, 0.2f
        );
    }
}

void Game::renderBirds()
{
    for (const auto& bird : m_birds)
    {
        if (bird.alive())
            // Yellow — alive
            m_renderer.drawCircle(bird.x(), bird.y(), Config::BIRD_RADIUS,
                                  1.0f, 0.9f, 0.0f);
        else
            // Dark red — dead (kept visible for debug; remove after Phase 1 testing)
            m_renderer.drawCircle(bird.x(), bird.y(), Config::BIRD_RADIUS,
                                  0.4f, 0.1f, 0.1f);
    }
}
