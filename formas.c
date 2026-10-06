#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "Formas");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);                       // 1. fundo

            DrawLine(400, 0, 400, 450, LIGHTGRAY);           // 2. objetos
            DrawRectangle(50, 200, 20, 80, BLUE);
            DrawCircle(400, 240, 12, RED);
            DrawTriangle((Vector2){600, 100}, (Vector2){550, 200}, (Vector2){650, 200}, GOLD);
            Color laranja = { 255, 100, 50, 255 };
            DrawRectangleRec((Rectangle){ 600, 300, 120, 60 }, laranja);

            DrawText("Placar: 3 x 2", 300, 20, 24, DARKGRAY);  // 3. interface por ultimo
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
