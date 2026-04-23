#include "Pipe.h"

Pipe::Pipe(float gapCenterY)
    : m_x(Config::PIPE_SPAWN_X)
    , m_gapCenterY(gapCenterY)
{
}

void Pipe::update(float dt)
{
    m_x -= Config::PIPE_SPEED * dt;
}
