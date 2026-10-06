# Mini desafios com Raylib

**Programação Imperativa e Funcional (PIF)** · CESAR School · 2026.2 · Prof. Roni Maciel

São oito mini jogos em três níveis, para você ganhar prática com a Raylib antes do projeto. Antes de começar, você já deve ter feito a instalação e os passos 1 a 6 do repositório da aula.

> ⚠️ **Ambiente**: tudo aqui roda no **Windows nativo** (terminal w64devkit) ou no **WSL**, exatamente como na aula. Os comandos são os mesmos do repositório da aula.

## O que entregar

| Item | Regra |
| --- | --- |
| Obrigatórios | Desafios **1** e **2**, mais **pelo menos um** do nível 2 (3, 4 ou 5) |
| Opcionais | Nível 3 (6, 7 e 8): bons pontos de partida para o projeto |
| Arquivos | Um arquivo por desafio, com o nome exato: `desafio1.c`, `desafio2.c`, ... `desafio8.c` |
| Compilação | `make desafioN` precisa compilar **sem erros** com o `Makefile` deste repositório |
| Entrega | Faça commit e push neste repositório até o prazo do assignment |

**Como cada desafio é avaliado**: cada critério da lista funcionando, o jogo compila, e o código é legível (nomes claros, `#define` para constantes, atualizar separado de desenhar).

## Como começar

```bash
# [Windows] no w64devkit   |   [WSL] no terminal do Ubuntu
cp molde.c desafio5.c       # parta do molde (ou de um arquivo vazio)
make desafio5
./desafio5.exe              # [Windows]
./desafio5                  # [WSL]
```

O [`molde.c`](molde.c) já traz:
- três telas (`MENU`, `JOGANDO`, `FIM`) controladas por um `enum`;
- `struct`s para o jogador e para os itens;
- funções separadas para **atualizar** (mudam o estado) e para **desenhar** (só leem o estado);
- um exemplo de *fold*: `contaAtivos` agrega um vetor num único número.

Deixe a [cheatsheet da Raylib](https://www.raylib.com/cheatsheet/cheatsheet.html) aberta numa aba enquanto programa.

## Visão geral

| # | Desafio | Nível | Conceitos praticados | Tempo estimado |
| --- | --- | --- | --- | --- |
| 1 | Minha cena | 1 | Formas, cores RGBA, ordem de desenho | 20 min |
| 2 | Pincel do mouse | 1 | Mouse, `GetRandomValue`, roda do mouse | 20 min |
| 3 | Personagem livre | 2 | Teclado, delta time, limites da tela | 30 min |
| 4 | Clique no alvo | 2 | Colisão ponto × círculo, cronômetro, placar | 40 min |
| 5 | Coletor de moedas | 2 | Vetor de `struct`, colisão círculo × retângulo, fold | 45 min |
| 6 | Navinha que atira | 3 | `IsKeyPressed`, vetor de projéteis, map | 60 min |
| 7 | Chuva de meteoros | 3 | Estados de jogo (`enum`), dificuldade crescente | 60 min |
| 8 | Mini Breakout | 3 | Grade de tijolos, quique, vitória e derrota | 90 min |

---

## Nível 1 — Aquecimento

### Desafio 1 — Minha cena · `desafio1.c`

Desenhe uma paisagem parada: céu, chão, uma casa (retângulo com um triângulo de telhado), um sol e uma árvore. Escreva seu nome no canto.

- [ ] Pelo menos 6 formas de 3 tipos diferentes
- [ ] Pelo menos 1 cor criada por você em RGBA, por exemplo `(Color){ 135, 206, 235, 255 }`
- [ ] O nome aparece por cima de tudo (ordem de desenho correta)

**Funções**: `DrawRectangle`, `DrawCircle`, `DrawTriangle` (vértices em sentido anti-horário), `DrawLine`, `DrawText`.
**Extra**: faça o sol "pulsar", variando o raio com `GetTime()`.

### Desafio 2 — Pincel do mouse · `desafio2.c`

Um círculo segue o cursor. O clique esquerdo sorteia uma cor nova; a roda do mouse aumenta ou diminui o raio.

- [ ] O círculo acompanha o mouse em todos os quadros
- [ ] Cada clique (não segurar) troca a cor uma única vez
- [ ] O raio fica entre 5 e 100, e o valor atual aparece na tela

**Funções**: `GetMousePosition`, `IsMouseButtonPressed`, `GetMouseWheelMove`, `GetRandomValue(0, 255)`.
**Extra**: transforme num programa de pintura. Segurando o botão direito, guarde posição, cor e raio num vetor de até 500 "pinceladas" e desenhe todas a cada quadro. **C** limpa a tela.

---

## Nível 2 — Primeiras regras

### Desafio 3 — Personagem livre · `desafio3.c`

Um quadrado anda com **WASD** a 250 pixels por segundo. Segurando **Shift**, corre a 500. Ele nunca sai da tela.

- [ ] Todo movimento é multiplicado por `GetFrameTime()`
- [ ] As 4 bordas bloqueiam o personagem
- [ ] A velocidade atual aparece na tela

**Funções**: `IsKeyDown(KEY_LEFT_SHIFT)`, `TextFormat`.
**Dica**: na diagonal o personagem anda mais rápido (cerca de 1,41×). Consegue corrigir?

### Desafio 4 — Clique no alvo · `desafio4.c`

Um alvo circular aparece numa posição aleatória. Clicou no alvo: +1 ponto, e ele muda de lugar e encolhe um pouco. A partida dura 30 segundos.

- [ ] Cronômetro regressivo visível, em segundos
- [ ] Clique fora do alvo não pontua
- [ ] Ao zerar o tempo, aparece "Fim! Pontos: N"; **R** reinicia

**Funções**: `CheckCollisionPointCircle(mouse, centro, raio)`, `GetRandomValue`.
**Dica**: guarde `float tempo = 30;` e subtraia `dt` a cada quadro, como o "Ponto!" do laboratório.

### Desafio 5 — Coletor de moedas · `desafio5.c`

Partindo do molde: 10 moedas espalhadas pela tela e um jogador que anda nas 4 direções. Encostou numa moeda, ela some e vale 1 ponto. Pegou todas, vitória.

- [ ] Moedas guardadas num vetor de `struct` com o campo `ativo`
- [ ] Colisão feita com `CheckCollisionCircleRec`
- [ ] Moedas restantes contadas por uma função separada (fold)
- [ ] Tela de vitória com o tempo total gasto

**Extra**: um inimigo que persegue o jogador, movendo a posição dele um pouco em direção ao jogador a cada quadro.

---

## Nível 3 — Mini jogos completos

### Desafio 6 — Navinha que atira · `desafio6.c`

Uma nave (triângulo) anda na horizontal, embaixo da tela. Cada toque em **Espaço** dispara **um** projétil, que sobe. Alvos atravessam a tela no alto; acertou, ganha ponto.

- [ ] Projéteis num vetor fixo, por exemplo `Projetil tiros[20]`, reaproveitando os inativos
- [ ] Um tiro por toque: `IsKeyPressed`, nunca `IsKeyDown`
- [ ] Projétil que sai da tela vira inativo
- [ ] Um laço atualiza todos os projéteis com a mesma função (map)

**Extra**: segurando a tecla, dispare no máximo 1 tiro a cada 0,3 s, controlado por um temporizador.

### Desafio 7 — Chuva de meteoros · `desafio7.c`

O jogador desvia de círculos que caem do topo com velocidades sorteadas. A cada 10 s, a chuva fica mais rápida. Encostou, perdeu.

- [ ] Três telas com `enum`: `MENU`, `JOGANDO` e `FIM` (como no molde)
- [ ] Meteoro que passa do chão volta ao topo numa posição `x` sorteada
- [ ] Pontuação = tempo sobrevivido; recorde guardado enquanto o jogo está aberto
- [ ] **R** reinicia tudo sem fechar a janela

**Funções**: `CheckCollisionCircleRec`, `GetRandomValue`.
**Dica**: escreva uma função `void reiniciaJogo(...)` e chame-a no início e quando apertar **R**.

### Desafio 8 — Mini Breakout · `desafio8.c`

Uma raquete embaixo, uma bola e uma grade de 5 × 10 tijolos no topo. A bola quica nas paredes, na raquete e nos tijolos, e cada tijolo atingido some. São 3 vidas.

- [ ] Tijolos num vetor (ou matriz) de `struct` com `Rectangle` e `ativo`
- [ ] A bola inverte `vel.y` ao bater num tijolo, e só um tijolo some por quadro
- [ ] Vitória quando o fold `tijolosAtivos(...)` chega a 0; derrota quando as vidas acabam
- [ ] Cada linha de tijolos tem uma cor diferente

**Funções**: `CheckCollisionCircleRec`, `DrawRectangleRec`, `DrawRectangleLinesEx`.
**Dica**: reaproveite o quique do Pong, incluindo a correção da bola "grudada" na raquete.

---

### Extra para quem terminou tudo · `desafio9.c`

Um Pong contra o computador: a raquete 2 segue `bola.pos.y`, mas com velocidade máxima limitada, para ser vencível.
