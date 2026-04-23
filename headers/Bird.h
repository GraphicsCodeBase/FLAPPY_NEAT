#pragma once
#include "config.h"

class Bird {
public:
    void reset();
    void flap();
    void update(float dt);

    float x()     const { return m_x; }
    float y()     const { return m_y; }
    float vy()    const { return m_vy; }
    bool  alive() const { return m_alive; }
    float fitness() const { return m_fitness; }

    void kill()             { m_alive = false; }
    void addFitness(float f){ m_fitness += f; }

private:
    float m_x      = Config::BIRD_X;
    float m_y      = 0.5f;
    float m_vy     = 0.0f;
    bool  m_alive  = true;
    float m_fitness = 0.0f;
};
