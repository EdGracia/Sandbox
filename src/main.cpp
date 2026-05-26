#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>

using namespace std;

int main(void) {
    // Initialization
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "sandbox");

    // Define the camera to look into our 3d world
    Camera3D camera;
    camera.position = (Vector3){0.0f, 20.0f, 20.0f}; // Camera position
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};     // Camera looking at point
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};         //(rotation towards target)
    camera.fovy = 60.0f;                             // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;          // Camera mode type

    // floating cube
    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
    Mesh cubeMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model cube = LoadModelFromMesh(cubeMesh);
    float rotation = 0.0f;

    Vector3 floorPosition = {0.0f, -2.0f, 0.0f};
    Vector3 floorSize = {20.0f, 2.0f, 20.0f};
    Mesh floorMesh = GenMeshCube(floorSize.x, floorSize.y, floorSize.z);
    Model floorModel = LoadModelFromMesh(floorMesh);
    BoundingBox floorBox = GetModelBoundingBox(floorModel);

    Player newPlayer({0.0f, 10.0f, -5.0f});
    newPlayer.setRadius(0.7f);

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update

        float dt = GetFrameTime();
        newPlayer.Update(dt, floorBox);

        rotation += 60.0f * GetFrameTime();
        cube.transform = MatrixRotateY(DEG2RAD * rotation);

        // Draw
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawCubeV(floorPosition, floorSize, WHITE);
        DrawModel(cube, cubePosition, 1.0f, RED);
        DrawModel(newPlayer.getModel(), newPlayer.getPosition(), 1.0f, BLUE);
        DrawModelWires(cube, cubePosition, 1.0f, PINK);
        DrawGrid(20, 1.0f);
        EndMode3D();

        EndDrawing();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(cube);
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
