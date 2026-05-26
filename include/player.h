#pragma once
#include "GameObject.h"
#include "raylib.h"
class Player : public GameObject {
    private:
        Vector3 velocity;
        float playerRadius = 1.0f;

        Mesh mesh;
        Model model;

        bool grounded;

    public:
        Player(Vector3 pos = {0.0f, 0.0f, 0.0f});

        Model getModel();
        float getRadius();
        void setRadius(float r);
        bool isOnGround(BoundingBox &box);

        void Update(float deltaTime, BoundingBox &ground);
};
