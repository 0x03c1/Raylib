#include "raylib.h"

#define LARGURA 800
#define ALTURA  450

int main(void) {
    InitWindow(LARGURA, ALTURA, "Bola que quica");
    SetTargetFPS(60);

    Vector2 bola = { 400, 225 };
    Vector2 vel  = { 300, 240 };          // pixels por SEGUNDO
    float raio = 12;

    while (!WindowShouldClose()) {
        // 1. ENTRADA + 2. ATUALIZAR
        float dt = GetFrameTime();
        bola.x += vel.x * dt;
        bola.y += vel.y * dt;

        if (bola.x - raio <= 0 || bola.x + raio >= LARGURA) vel.x = -vel.x;
        if (bola.y - raio <= 0 || bola.y + raio >= ALTURA)  vel.y = -vel.y;

        // 3. DESENHAR
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircleV(bola, raio, RED);
            DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
