#pragma once

namespace Config {

	// --- Window ------------------------------------------------------------------
	inline constexpr int   WINDOW_W = 1280;
	inline constexpr int   WINDOW_H = 720;

	// --- World coordinate space: [0,1] x [0,1] -----------------------------------
	inline constexpr float GRAVITY = -9.8f;
	inline constexpr float FLAP_IMPULSE = 3.2f;
	inline constexpr float MAX_FALL_SPEED = -5.0f;
	inline constexpr float BIRD_X = 0.25f;
	inline constexpr float BIRD_RADIUS = 0.025f;

	// --- Pipes -------------------------------------------------------------------
	inline constexpr float PIPE_WIDTH = 0.08f;
	inline constexpr float PIPE_GAP = 0.22f;
	inline constexpr float PIPE_SPEED = 0.15f;
	inline constexpr float PIPE_SPAWN_X = 1.05f;
	inline constexpr float PIPE_GAP_MIN_Y = 0.20f;
	inline constexpr float PIPE_GAP_MAX_Y = 0.80f;
	inline constexpr float PIPE_SPAWN_INTERVAL = 2.4f;

	// --- Physics timestep --------------------------------------------------------
	inline constexpr float FIXED_DT = 1.0f / 60.0f;

	// --- NEAT --------------------------------------------------------------------
	inline constexpr int   POPULATION_SIZE = 150;
	inline constexpr int   INPUTS = 5;
	inline constexpr int   OUTPUTS = 1;

	// Speciation
	inline constexpr float COMPAT_THRESHOLD = 3.0f;
	inline constexpr float COMPAT_C1 = 1.0f;
	inline constexpr float COMPAT_C2 = 1.0f;
	inline constexpr float COMPAT_C3 = 0.4f;

	// Mutation rates
	inline constexpr float MUTATE_WEIGHT_RATE = 0.8f;
	inline constexpr float MUTATE_WEIGHT_PERTURB = 0.9f;
	inline constexpr float MUTATE_ADD_NODE = 0.03f;
	inline constexpr float MUTATE_ADD_CONN = 0.05f;
	inline constexpr float MUTATE_TOGGLE_CONN = 0.01f;

	// Reproduction
	inline constexpr float CROSSOVER_RATE = 0.75f;
	inline constexpr int   STAGNATION_LIMIT = 15;
	inline constexpr float CULL_FRACTION = 0.5f;
	inline constexpr int   ELITISM_COUNT = 1;

	// Fitness
	inline constexpr float FITNESS_FRAME_WEIGHT = 0.01f;
	inline constexpr float FITNESS_PIPE_WEIGHT = 5.0f;

	// Neural net activation
	inline constexpr float SIGMOID_SCALE = 4.9f;

} // namespace Config
