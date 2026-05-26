#pragma once
#include "raylib.h"

class GameObject {
    protected:
        Vector3 position;
        Vector3 size;
        Vector3 rotation;

    public:
        GameObject(Vector3 p = {0.0f, 0.0f, 0.0f},
                   Vector3 s =
                       {
                           1.0f,
                           1.0f,
                           1.0f,
                       },
                   Vector3 r = {0.0f, 0.0f, 0.0f});
        Vector3 getPosition();
        Vector3 getSize();
        Vector3 getRotation();
        void setPosition(Vector3 pos);
        void setSize(Vector3 size);
        void setRotation(Vector3 rotation);
};
