#include "Bird.h"
#include <algorithm>

void Bird::reset()
{
    m_x       = Config::BIRD_X;
    m_y       = 0.5f;
    m_vy      = 0.0f;
    m_alive   = true;
    m_fitness = 0.0f;
}

void Bird::flap()
{
    m_vy = Config::FLAP_IMPULSE;
}

void Bird::update(float dt)
{
    if (!m_alive) return;

    m_vy += Config::GRAVITY * dt;
    m_vy  = std::max(m_vy, Config::MAX_FALL_SPEED);
    m_y  += m_vy * dt;

    // Kill if out of bounds
    if (m_y < 0.0f || m_y > 1.0f)
        m_alive = false;
}
