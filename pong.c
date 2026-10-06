#include "raylib.h"

#define LARGURA 800
#define ALTURA  450

typedef struct { Vector2 pos, vel; float raio; } Bola;
typedef struct { Rectangle rec; int pontos; }      Raquete;

int main(void) {
    InitWindow(LARGURA, ALTURA, "Pong - PIF");
    SetTargetFPS(60);

    Bola bola  = { {LARGURA/2, ALTURA/2}, {300, 250}, 10 };
    Raquete p1 = { {30, ALTURA/2 - 40, 15, 80}, 0 };
    Raquete p2 = { {LARGURA - 45, ALTURA/2 - 40, 15, 80}, 0 };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // jogador 1: W (sobe) e S (desce)
        if (IsKeyDown(KEY_W)) p1.rec.y -= 400 * dt;
        if (IsKeyDown(KEY_S)) p1.rec.y += 400 * dt;
        // jogador 2: setas
        if (IsKeyDown(KEY_UP))   p2.rec.y -= 400 * dt;
        if (IsKeyDown(KEY_DOWN)) p2.rec.y += 400 * dt;

        // move a bola
        bola.pos.x += bola.vel.x * dt;
        bola.pos.y += bola.vel.y * dt;

        // quica no topo e no fundo
        if (bola.pos.y < 0 || bola.pos.y > ALTURA)
            bola.vel.y = -bola.vel.y;

        // quica nas raquetes (so se a bola estiver indo NA DIRECAO da raquete,
        // senao ela inverte varias vezes seguidas e "gruda")
        if (CheckCollisionCircleRec(bola.pos, bola.raio, p1.rec) && bola.vel.x < 0) bola.vel.x = -bola.vel.x;
        if (CheckCollisionCircleRec(bola.pos, bola.raio, p2.rec) && bola.vel.x > 0) bola.vel.x = -bola.vel.x;

        // ponto: bola saiu pela esquerda ou direita
        if (bola.pos.x < 0)       { p2.pontos++; bola.pos = (Vector2){LARGURA/2, ALTURA/2}; }
        if (bola.pos.x > LARGURA) { p1.pontos++; bola.pos = (Vector2){LARGURA/2, ALTURA/2}; }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawLine(LARGURA/2, 0, LARGURA/2, ALTURA, GRAY);
            DrawRectangleRec(p1.rec, RAYWHITE);
            DrawRectangleRec(p2.rec, RAYWHITE);
            DrawCircleV(bola.pos, bola.raio, RED);
            DrawText(TextFormat("%d", p1.pontos), 200, 20, 40, RAYWHITE);
            DrawText(TextFormat("%d", p2.pontos), 580, 20, 40, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
