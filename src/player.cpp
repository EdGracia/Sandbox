#include "player.h"
#include "physics.h"

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
    if (CheckCollisionBoxSphere(box, position, playerRadius))
        grounded = true;
    return grounded;
}

void Player::Update(float deltaTime, BoundingBox &ground) {
    if (!isOnGround(ground))
        Physics::ApplyGravity(velocity.y, deltaTime, 9.8);
    // Update position
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    position.z += velocity.z * deltaTime;
}
