#include "raylib.h"

int main(void) {
    InitWindow(800, 450, "Meu primeiro jogo");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {      // ate fechar a janela (ou apertar ESC)
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Ola, Raylib!", 300, 200, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
