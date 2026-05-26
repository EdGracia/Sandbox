#pragma once
#include "GameObject.h"
#include "raylib.h"
class Player : public GameObject {
    private:
        Vector3 velocity = {0.0f, 0.0f, 0.0f};
        float moveSpeed = 20.0f;
        float jumpForce = 10.0f;
        float friction = 2.5f; // smoother the lower it is
        float playerRadius = 1.0f;

        Mesh mesh;
        Model model;

        bool grounded;

    public:
        Player(Vector3 pos = {0.0f, 0.0f, 0.0f});

        Model getModel();
        float getRadius();
        Vector3 getVelocity() { return velocity; };
        void setRadius(float r);
        bool isOnGround(BoundingBox &box);
        void handleInput(float deltaTime);

        void Update(float deltaTime, BoundingBox &ground);
};
