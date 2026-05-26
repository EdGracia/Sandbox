#include "player.h"
#include "physics.h"
#include "raymath.h"
#include <cmath>
#include <iostream>

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
        std::cout << "collided!" << std::endl;
        grounded = true;
        velocity.y = 0.0f;
    } else {
        grounded = false;
    }
    return grounded;
}

void Player::handleInput(float deltaTime) {
    if (!grounded) {
        return;
    }

    if (IsKeyPressed(KEY_SPACE)) {
        if (grounded) { // prevents double jump
            grounded = false;
            velocity.y += jumpForce;
        }
    }
    if (IsKeyDown(KEY_A)) {
        velocity.x -= moveSpeed * deltaTime;
    } else if (IsKeyDown(KEY_D)) {
        velocity.x += moveSpeed * deltaTime;
    } else if (IsKeyDown(KEY_W)) {
        velocity.z -= moveSpeed * deltaTime;
    } else if (IsKeyDown(KEY_S)) {
        velocity.z += moveSpeed * deltaTime;
    } else if (IsKeyDown(KEY_R)) {
        position = {0.0f, 10.0f, 0.0f};
        velocity = Vector3Zero();
    } else {
        velocity.x *= exp(-friction * deltaTime);
        velocity.z *= exp(-friction * deltaTime);
    }
}

void Player::Update(float deltaTime, BoundingBox &ground) {
    isOnGround(ground);
    handleInput(deltaTime);
    if (!grounded) {
        Physics::ApplyGravity(velocity.y, deltaTime, 9.8);
    }

    // Physics::ApplyGravity(velocity.y, deltaTime, 9.8);
    // Update position
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;
}
