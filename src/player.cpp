#include "player.h"
#include "physics.h"
#include "raymath.h"
#include <cmath>

Player::Player(Vector3 pos)
    : GameObject(pos) {
    mesh = GenMeshSphere(playerRadius, 20, 20);
    model = LoadModelFromMesh(mesh);
}

Model Player::getModel() { return model; }
float Player::getRadius() { return playerRadius; }
void Player::setRadius(float r) {
    playerRadius = r;
    mesh = GenMeshSphere(playerRadius, 20, 20);
    model = LoadModelFromMesh(mesh);
}

bool Player::isOnGround(BoundingBox &box) {
    if (CheckCollisionBoxSphere(box, position, playerRadius)) {
        grounded = true;
        velocity.y = 0.0f;
        position.y = box.max.y + playerRadius;
    } else {
        grounded = false;
    }
    return grounded;
}

void Player::handleInput(float deltaTime, float cameraYaw) {
    if (IsKeyDown(KEY_R)) {
        position = {0.0f, 10.0f, 0.0f};
        velocity = Vector3Zero();
    }

    if (!grounded) return;

    if (IsKeyPressed(KEY_SPACE)) {
        grounded = false;
        velocity.y += jumpForce;
    }

    // Movement vectors relative to camera yaw
    float fwdX = -sinf(cameraYaw);
    float fwdZ = -cosf(cameraYaw);
    float rgtX =  cosf(cameraYaw);
    float rgtZ = -sinf(cameraYaw);

    float moveX = 0.0f, moveZ = 0.0f;
    if (IsKeyDown(KEY_W)) { moveX += fwdX; moveZ += fwdZ; }
    if (IsKeyDown(KEY_S)) { moveX -= fwdX; moveZ -= fwdZ; }
    if (IsKeyDown(KEY_A)) { moveX -= rgtX; moveZ -= rgtZ; }
    if (IsKeyDown(KEY_D)) { moveX += rgtX; moveZ += rgtZ; }

    if (moveX != 0.0f || moveZ != 0.0f) {
        float len = sqrtf(moveX * moveX + moveZ * moveZ);
        velocity.x += (moveX / len) * moveSpeed * deltaTime;
        velocity.z += (moveZ / len) * moveSpeed * deltaTime;
        // Clamp horizontal speed
        float hSpeed = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
        if (hSpeed > maxHorizontalSpeed) {
            float scale = maxHorizontalSpeed / hSpeed;
            velocity.x *= scale;
            velocity.z *= scale;
        }
    } else {
        velocity.x *= expf(-friction * deltaTime);
        velocity.z *= expf(-friction * deltaTime);
    }
}

void Player::Update(float deltaTime, BoundingBox &ground, float cameraYaw) {
    isOnGround(ground);
    handleInput(deltaTime, cameraYaw);
    if (!grounded) {
        Physics::ApplyGravity(velocity.y, deltaTime, 9.8f);
    }
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;
}
