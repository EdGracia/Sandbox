#pragma once
#include "GameObject.h"
#include "raylib.h"
class Player : public GameObject {
    private:
        Vector3 velocity = {0.0f, 0.0f, 0.0f};
        float moveSpeed = 20.0f;
        float airMoveSpeed = moveSpeed / 4.0f;
        float maxHorizontalSpeed = 8.0f;
        float jumpForce = 10.0f;
        float friction = 3.5f;
        float playerRadius = 1.0f;

        Mesh mesh;
        Model model;

        bool grounded = false;

        float dashSpeed = 18.0f;
        float dashCooldown = 0.8f;
        float dashCooldownTimer = 0.0f;
        float lastMoveDirX = 0.0f;
        float lastMoveDirZ = -1.0f;

    public:
        Player(Vector3 pos = {0.0f, 0.0f, 0.0f});

        Model getModel();
        float getRadius();
        Vector3 getVelocity() { return velocity; };
        void setRadius(float r);
        bool isOnGround(BoundingBox &box);
        void handleInput(float deltaTime, float cameraYaw);

        void Update(float deltaTime, BoundingBox &ground, float cameraYaw);
};
