# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run

```bash
make        # compile all src/*.cpp → ./main
make run    # compile and launch the game
make clean  # remove ./main
```

Requires raylib installed via Homebrew (`/opt/homebrew/opt/raylib`). Built with `clang++` and C++17.

## Architecture

This is a 3D game sandbox built with [raylib](https://www.raylib.com/). All headers live in `include/`, all implementation files in `src/`.

**Class hierarchy:**
- `GameObject` (`include/gameObject.h`, `src/gameobject.cpp`) — base class holding `position`, `size`, `rotation` as `Vector3` with accessors/mutators.
- `Player : GameObject` (`include/player.h`, `src/player.cpp`) — owns its own `Mesh`/`Model` (a sphere), velocity, and movement state. Handles input (WASD + Space to jump, R to reset), collision with a floor `BoundingBox`, and per-frame physics integration.
- `Physics` namespace (`include/physics.h`) — stateless inline helpers; currently only `ApplyGravity`.

**Game loop (`src/main.cpp`):**
- Creates a `Camera3D`, a floor mesh/model, a decorative rotating cube, and a `Player`.
- Each frame: calls `Player::Update(deltaTime, floorBox)` → then manually tracks the camera behind the player using mouse delta.
- Cursor is disabled (`DisableCursor()`) for mouse-look; no fixed FPS cap (commented out).

**Player::Update flow:**
1. `isOnGround(ground)` — sphere-vs-box collision; zeros `velocity.y` and sets `grounded` on hit.
2. `handleInput(deltaTime)` — WASD accelerates velocity, friction applied via `exp(-friction * dt)` when no key held; Space triggers jump; movement only allowed while grounded.
3. `drawAngle()` — renders a directional indicator model at the player position (WIP).
4. `Physics::ApplyGravity` applied when not grounded.
5. Position integrated from velocity.

## Active branch

`feature/follow-camera` — work in progress on making the camera follow the player smoothly.
