#include "player.h"
#include "raylib.h"
#include "raymath.h"

void drawCoordinates(Vector3 position, const int xPos, const int yPos) {
    DrawText(TextFormat("%.1f", position.x), xPos, yPos, 20, BLACK);
    DrawText(TextFormat(", %.1f", position.y), xPos + 50, yPos, 20, BLACK);
    DrawText(TextFormat(", %.1f", position.z), xPos + 100, yPos, 20, BLACK);
}

int main(void) {
    InitWindow(0, 0, "sandbox");

    Camera3D camera = {};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Third-person camera state
    float cameraYaw = 0.0f;   // radians, horizontal
    float cameraPitch = 0.4f; // radians, vertical (positive = above player)
    float cameraDistance = 15.0f;
    const float sensitivity = 0.003f;

    // Floating cube
    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
    Mesh cubeMesh = GenMeshCube(1.0f, 1.0f, 1.0f);
    Model cube = LoadModelFromMesh(cubeMesh);
    float rotation = 0.0f;

    Vector3 floorPosition = {0.0f, -2.0f, 0.0f};
    Vector3 floorSize = {20.0f, 2.0f, 20.0f};
    Mesh floorMesh = GenMeshCube(floorSize.x, floorSize.y, floorSize.z);
    Model floorModel = LoadModelFromMesh(floorMesh);
    BoundingBox floorBox = GetModelBoundingBox(floorModel);
    // GetModelBoundingBox returns model-space coords; translate to world space.
    floorBox.min = Vector3Add(floorBox.min, floorPosition);
    floorBox.max = Vector3Add(floorBox.max, floorPosition);

    Player newPlayer({0.0f, 5.0f, 0.0f});
    newPlayer.setRadius(0.7f);

    SetTargetFPS(60);
    DisableCursor();

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // Update camera angles from mouse
        cameraYaw += GetMouseDelta().x * sensitivity;
        cameraPitch -= GetMouseDelta().y * sensitivity;
        if (cameraPitch > 1.3f)
            cameraPitch = 1.3f; // ~75 deg up
        if (cameraPitch < 0.05f)
            cameraPitch = 0.05f; // keep camera above floor

        newPlayer.Update(deltaTime, floorBox, cameraYaw);
        Vector3 playerPos = newPlayer.getPosition();

        // Orbit camera around player
        camera.position = {
            playerPos.x + cameraDistance * sinf(cameraYaw) * cosf(cameraPitch),
            playerPos.y + cameraDistance * sinf(cameraPitch),
            playerPos.z + cameraDistance * cosf(cameraYaw) * cosf(cameraPitch)};
        camera.target = {playerPos.x, playerPos.y + 1.0f, playerPos.z};

        rotation += 60.0f * deltaTime;
        cube.transform = MatrixRotateY(DEG2RAD * rotation);

        BeginDrawing();
        ClearBackground(DARKGRAY);

        BeginMode3D(camera);
        DrawModel(floorModel, floorPosition, 1.0f, WHITE);
        DrawModelWires(floorModel, floorPosition, 1.0f, GRAY);
        DrawModel(cube, cubePosition, 1.0f, RED);
        DrawModelWires(cube, cubePosition, 1.0f, MAROON);
        DrawModel(newPlayer.getModel(), playerPos, 1.0f, BLUE);
        DrawModelWires(newPlayer.getModel(), playerPos, 1.0f, DARKBLUE);
        EndMode3D();

        DrawFPS(10, 10);
        DrawText("Player Position: ", 10, 30, 20, BLACK);
        drawCoordinates(playerPos, 10, 50);
        DrawText(
            TextFormat("Camera Yaw: %.2f  Pitch: %.2f", cameraYaw, cameraPitch),
            10, 70, 20, BLACK);

        EndDrawing();
    }

    UnloadModel(cube);
    UnloadModel(floorModel);
    CloseWindow();

    return 0;
}
