#include "raylib.h"

#define LARGURA 800
#define ALTURA  450

int main(void) {
    InitWindow(LARGURA, ALTURA, "Mover com as setas");
    SetTargetFPS(60);

    Rectangle jogador = { 380, 200, 40, 40 };
    Color cor = BLUE;

    while (!WindowShouldClose()) {
        // 1. ENTRADA + 2. ATUALIZAR
        if (IsKeyDown(KEY_RIGHT)) jogador.x += 5;
        if (IsKeyDown(KEY_LEFT))  jogador.x -= 5;
        if (IsKeyDown(KEY_UP))    jogador.y -= 5;   // y cresce para BAIXO
        if (IsKeyDown(KEY_DOWN))  jogador.y += 5;

        if (IsKeyPressed(KEY_SPACE)) cor = (cor.r == BLUE.r) ? RED : BLUE;  // troca 1x por toque

        Vector2 mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            jogador.x = mouse.x - jogador.width / 2;      // teletransporta para o clique
            jogador.y = mouse.y - jogador.height / 2;
        }

        // 3. DESENHAR
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangleRec(jogador, cor);
            DrawText(TextFormat("x = %.0f  y = %.0f", jogador.x, jogador.y), 10, 10, 20, DARKGRAY);
            DrawText("Setas: mover | Espaco: cor | Clique: teletransporte", 10, 420, 18, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
