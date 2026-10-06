#include "raylib.h"

#define LARGURA 800
#define ALTURA  450
#define MAX_ITENS 10

typedef enum { MENU, JOGANDO, FIM } Estado;          // telas do jogo

typedef struct {
    Rectangle rec;
    float velocidade;                                // pixels por segundo
} Jogador;

typedef struct {
    Vector2 pos;
    float raio;
    bool ativo;                                      // false = some do jogo
} Item;

// ---------- logica (atualizar): muda o estado, nao desenha ----------
void atualizaJogador(Jogador *j, float dt) {
    if (IsKeyDown(KEY_A)) j->rec.x -= j->velocidade * dt;
    if (IsKeyDown(KEY_D)) j->rec.x += j->velocidade * dt;
    if (j->rec.x < 0) j->rec.x = 0;
    if (j->rec.x > LARGURA - j->rec.width) j->rec.x = LARGURA - j->rec.width;
}

int contaAtivos(const Item itens[], int n) {         // "fold": agrega a lista num numero
    int total = 0;
    for (int i = 0; i < n; i++)
        if (itens[i].ativo) total++;
    return total;
}

// ---------- desenho: so le o estado ----------
void desenhaJogador(Jogador j) { DrawRectangleRec(j.rec, BLUE); }

void desenhaItens(const Item itens[], int n) {
    for (int i = 0; i < n; i++)
        if (itens[i].ativo) DrawCircleV(itens[i].pos, itens[i].raio, GOLD);
}

int main(void) {
    InitWindow(LARGURA, ALTURA, "Meu mini jogo");
    SetTargetFPS(60);

    Estado estado = MENU;
    Jogador jogador = { { LARGURA/2 - 25, ALTURA - 40, 50, 20 }, 400 };
    Item itens[MAX_ITENS];
    for (int i = 0; i < MAX_ITENS; i++)
        itens[i] = (Item){ { GetRandomValue(20, LARGURA - 20), GetRandomValue(20, ALTURA - 100) }, 10, true };

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // 1. ENTRADA + 2. ATUALIZAR
        switch (estado) {
            case MENU:
                if (IsKeyPressed(KEY_ENTER)) estado = JOGANDO;
                break;
            case JOGANDO:
                atualizaJogador(&jogador, dt);
                // TODO: sua regra aqui (colisoes, pontos, inimigos...)
                if (contaAtivos(itens, MAX_ITENS) == 0) estado = FIM;
                break;
            case FIM:
                if (IsKeyPressed(KEY_R)) estado = MENU;
                break;
        }

        // 3. DESENHAR
        BeginDrawing();
            ClearBackground(RAYWHITE);
            if (estado == MENU) {
                DrawText("MEU MINI JOGO", 260, 160, 40, DARKBLUE);
                DrawText("ENTER para comecar", 290, 230, 20, GRAY);
            } else if (estado == JOGANDO) {
                desenhaItens(itens, MAX_ITENS);
                desenhaJogador(jogador);
                DrawText(TextFormat("Restam: %d", contaAtivos(itens, MAX_ITENS)), 10, 10, 20, DARKGRAY);
            } else {
                DrawText("FIM!", 350, 180, 40, MAROON);
                DrawText("R para voltar ao menu", 280, 240, 20, GRAY);
            }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
