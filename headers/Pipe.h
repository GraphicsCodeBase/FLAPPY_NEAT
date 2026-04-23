#pragma once
#include "config.h"

class Pipe {
public:
    explicit Pipe(float gapCenterY);

    void update(float dt);

    float x()         const { return m_x; }
    float gapCenterY()const { return m_gapCenterY; }
    float gapTop()    const { return m_gapCenterY + Config::PIPE_GAP * 0.5f; }
    float gapBottom() const { return m_gapCenterY - Config::PIPE_GAP * 0.5f; }
    bool  passed()    const { return m_passed; }
    bool  offScreen() const { return m_x + Config::PIPE_WIDTH < 0.0f; }

    void markPassed() { m_passed = true; }

private:
    float m_x;
    float m_gapCenterY;
    bool  m_passed = false;
};
