#pragma once

namespace Physics {

// Gravity (clamps to terminal)
inline void ApplyGravity(float &vy, float dt, float g,
                         float terminal = 1200.0f) {
    vy -= g * dt;
    if (vy > terminal)
        vy = terminal;
}

} // namespace Physics
