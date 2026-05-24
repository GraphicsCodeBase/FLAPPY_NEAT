# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Goal

Measure how fast and how well a NEAT (NeuroEvolution of Augmenting Topologies) algorithm can learn to play Flappy Bird. The game engine and game objects are built; the NEAT algorithm itself is not yet implemented.

## Build Commands

Dependencies are managed via **vcpkg** (glfw3, glad, glm). Ensure vcpkg is integrated before configuring.

```powershell
# Configure (from repo root) — point to your vcpkg toolchain file
cmake -B out/build -S . -DCMAKE_TOOLCHAIN_FILE="<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake"

# Build
cmake --build out/build --config Release

# Run (assets are auto-copied next to the exe by the post-build step)
./out/build/Release/FlappyNEAT.exe
```

The CMake post-build step copies `assets/` next to the executable automatically, so shaders and fonts are always available at runtime relative to the exe.

## Architecture

### Coordinate System
All game logic and rendering use a **[0,1] × [0,1] world space**. The renderer applies a single orthographic projection (`glm::ortho(0,1,0,1,-1,1)`) via the `u_projection` uniform. Never use pixel coordinates in game logic — everything is normalized.

### Renderer (Batch / Immediate-mode hybrid)
`Renderer` accumulates all draw calls for a frame into CPU-side `m_vertices` / `m_indices` vectors, then uploads and issues a single `glDrawElements` call in `endFrame()`. Per-frame flow:

```
beginFrame()         → clears CPU vectors
drawQuad / drawCircle → appends to CPU vectors
endFrame()           → glBufferSubData + glDrawElements
```

GPU buffers are pre-allocated for 10 000 vertices / 30 000 indices (dynamic draw). The single shader (`assets/Shaders/Quad.vert/.frag`) handles both quads and circles — it only passes through position and per-vertex RGBA color.

### Shader Loading
Shaders are loaded **at runtime from the filesystem**, not embedded. `Shader::load()` reads `assets/Shaders/quad.vert` and `assets/Shaders/quad.frag` relative to the working directory (which is the exe directory after the CMake copy step). GLSL compile and link errors are printed to `stderr`.

### Game Objects
- **`Bird`** — fixed X position (`Config::BIRD_X = 0.25`), vertical physics only (gravity + flap impulse clamped to `MAX_FALL_SPEED`). Tracks `m_fitness` and `m_alive`. `update(dt)` uses the fixed timestep `Config::FIXED_DT = 1/60s`.
- **`Pipe`** — spawned at `PIPE_SPAWN_X = 1.05`, scrolls left at `PIPE_SPEED`. Exposes `gapTop()` / `gapBottom()` for collision. `offScreen()` and `passed()` flags drive cleanup and fitness scoring.

### What Is NOT Yet Implemented
`config.h` fully defines the NEAT hyperparameters but no NEAT code exists yet. The missing layer sits between the game objects and `main.cpp`:

- `Genome` — node/connection genes with innovation numbers
- `Network` — feed-forward evaluator (sigmoid with `Config::SIGMOID_SCALE = 4.9`)
- `Species` — compatibility distance (`C1·excess + C2·disjoint + C3·avgWeightDiff`) vs `COMPAT_THRESHOLD`
- `Population` — 150 agents, speciation, crossover (`CROSSOVER_RATE = 0.75`), mutation (weight perturb, add-node, add-conn, toggle), stagnation culling after 15 generations, elitism of 1

**NEAT inputs (5):** bird Y, bird velocity, horizontal distance to next pipe, next pipe gap top Y, next pipe gap bottom Y.  
**NEAT output (1):** > 0.5 → flap.  
**Fitness:** `frames_alive × 0.01 + pipes_passed × 5.0`.

### Key Config Knobs
All tunable parameters live in `headers/config.h` as `inline constexpr` values in the `Config` namespace. Change them there — do not hardcode magic numbers elsewhere.
