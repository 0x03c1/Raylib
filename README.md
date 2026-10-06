# Raylib: programando jogos em C

**Programação Imperativa e Funcional (PIF)** · CESAR School · 2026.2 · Prof. Roni Maciel

Material prático da aula: instalação da [Raylib](https://www.raylib.com/) e seis passos, do primeiro programa ao Pong modificado. Ao final você terá compilado e rodado uma janela, formas, um personagem controlado pelo teclado, uma bola que quica e um Pong para dois jogadores.

| Arquivo | Passo | O que faz |
| --- | --- | --- |
| [`hello.c`](hello.c) | 1 | Abre uma janela com "Ola, Raylib!" |
| [`formas.c`](formas.c) | 2 | Desenha linha, retângulos, círculo, triângulo e texto |
| [`mover.c`](mover.c) | 3 | Move um quadrado com as setas; espaço e clique do mouse |
| [`bola.c`](bola.c) | 4 | Bola que quica nas bordas usando delta time |
| [`pong.c`](pong.c) | 5 e 6 | Pong completo para dois jogadores |
| [`Makefile`](Makefile) | — | Compila tudo no Windows, no WSL e no macOS |

---

## ⚠️ Atenção: em qual sistema você vai rodar

**Você vai compilar e rodar no Windows**, seja no **Windows nativo** ou no **WSL** (Ubuntu dentro do Windows). O professor demonstra no macOS, mas **os comandos de macOS que aparecem na tela dele não servem para você**.

O código C é **idêntico** em todos os sistemas. Só mudam a instalação da Raylib e o comando de compilação:

| Ambiente | Para quem | Terminal | Executa com |
| --- | --- | --- | --- |
| **Windows nativo** (recomendado) | Todos os alunos, se não tiver preferência | w64devkit (vem no instalador oficial) | `./pong.exe` |
| **WSL 2 + Ubuntu** | Quem já programa no Ubuntu dentro do Windows | Terminal do Ubuntu | `./pong` |
| macOS | Só o professor (demonstração) | Terminal | `./pong` |

Neste README, cada comando vem marcado com o sistema a que pertence: **[Windows]**, **[WSL]** ou **[macOS]**.

---

## 1. Instalação (faça antes da aula)

Escolha **um** caminho. O teste final dos dois é o mesmo: o `hello.c` abre uma janela escrita "Ola, Raylib!".

### Caminho A — [Windows] instalador oficial (recomendado)

1. Acesse [raysan5.itch.io/raylib](https://raysan5.itch.io/raylib) e clique em **Download Now**. Para baixar de graça, clique em **No thanks, just take me to the downloads**.
2. Baixe **raylib 6.0 Windows Installer (64bit)** (cerca de 750 MB) e execute.
3. Mantenha a pasta padrão **`C:\raylib`**. Não mude: o Makefile e os comandos abaixo dependem dela.
4. O instalador traz tudo: a Raylib em `C:\raylib\raylib`, o compilador **w64devkit** (gcc + make) em `C:\raylib\w64devkit` e um Notepad++ configurado.
5. Abra o terminal do compilador: **`C:\raylib\w64devkit\w64devkit.exe`**. Todos os comandos [Windows] deste README são digitados nele, **não** no cmd nem no PowerShell.
6. Confira o compilador:

   ```bash
   # [Windows] dentro do w64devkit
   gcc --version
   make --version
   ```

7. Baixe este repositório (botão **Code → Download ZIP**, ou `git clone` se tiver o Git instalado), extraia em `Documentos` e entre na pasta. No w64devkit, use barras normais `/`:

   ```bash
   # [Windows] dentro do w64devkit
   cd C:/Users/$USERNAME/Documents/aula18-raylib
   make hello
   ./hello.exe
   ```

**Alternativa sem terminal**: abra o `.c` no Notepad++ do instalador (`C:\raylib\npp\notepad++.exe`), aperte **F6**, escolha **`raylib_compile_execute`** e clique OK.

### Caminho B — [WSL] Ubuntu dentro do Windows

1. No **PowerShell do Windows**, confira se o Ubuntu está no WSL **2** e atualize. A atualização traz o WSLg, que permite abrir janelas:

   ```powershell
   # [Windows - PowerShell]
   wsl -l -v          # a coluna VERSION precisa mostrar 2
   wsl --update
   wsl --shutdown     # reinicia o WSL para aplicar
   ```

   Se aparecer `VERSION 1`, converta com `wsl --set-version Ubuntu 2`. Se ainda não tem WSL, rode `wsl --install` e reinicie o PC.

2. No **Ubuntu**, instale o compilador e as dependências gráficas:

   ```bash
   # [WSL]
   sudo apt update
   sudo apt install -y build-essential git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
   ```

3. Baixe, compile e instale a Raylib 6.0 (leva de 1 a 3 minutos):

   ```bash
   # [WSL]
   cd ~
   git clone --depth 1 --branch 6.0 https://github.com/raysan5/raylib.git
   cd raylib/src
   make PLATFORM=PLATFORM_DESKTOP
   sudo make install
   ls /usr/local/lib/libraylib.a   # deve existir
   ```

4. Confira se o WSL consegue abrir janelas. Deve imprimir algo como `:0 wayland-0`:

   ```bash
   # [WSL]
   echo $DISPLAY $WAYLAND_DISPLAY
   ```

5. Clone este repositório **dentro do Linux** (é mais rápido que em `/mnt/c`) e teste:

   ```bash
   # [WSL]
   cd ~
   git clone <URL-deste-repositorio> aula18-raylib
   cd aula18-raylib
   make hello
   ./hello
   ```

   Para editar, use o VS Code com a extensão **WSL**: rode `code .` dentro da pasta.

### [macOS] só para referência

```bash
# [macOS]
brew install raylib
make hello && ./hello
```

---

## 2. Como compilar

Com o [`Makefile`](Makefile) deste repositório, o comando é o mesmo em qualquer sistema:

```bash
make            # compila todos os exemplos
make pong       # compila só o pong.c
make clean      # apaga os executáveis
```

| Ambiente | Executar | Comando sem Makefile |
| --- | --- | --- |
| **[Windows]** w64devkit | `./pong.exe` | `gcc pong.c -o pong.exe -Wall -std=c99 -IC:/raylib/raylib/src -LC:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -lshcore` |
| **[WSL]** Ubuntu | `./pong` | `gcc pong.c -o pong -Wall -std=c99 -lraylib -lGL -lm -lpthread -ldl -lrt -lX11` |

- No Windows, o gcc acrescenta `.exe` sozinho: `make pong` gera `pong.exe`.
- As bibliotecas `-l...` vêm sempre **depois** do arquivo `.c`.
- Se instalou a Raylib fora de `C:\raylib`, informe o caminho: `make RAYLIB=D:/outro/caminho/raylib/src`.
- Para fechar qualquer programa, feche a janela ou aperte **ESC**.

---

## 3. Passo a passo

O game loop de todo jogo Raylib tem sempre três etapas, repetidas 60 vezes por segundo:

```
1. ENTRADA (teclado, mouse)  →  2. ATUALIZAR (mover, colidir, pontuar)  →  3. DESENHAR (mostrar na tela)
```

### Passo 1 — Hello, Window · [`hello.c`](hello.c)

```bash
make hello
```

**Resultado esperado**: janela branca de 800×450 com o título "Meu primeiro jogo" e o texto "Ola, Raylib!" no meio.

**Experimente**: mude o tamanho da janela, a cor do fundo e a posição do texto. Rode a cada mudança.

### Passo 2 — Desenhando formas · [`formas.c`](formas.c)

**Resultado esperado**: linha cinza no meio, raquete azul à esquerda, bola vermelha no centro, triângulo dourado e retângulo laranja à direita, placar no topo.

**Experimente**:
- Desenhe o `DrawText` antes do `ClearBackground`. O que acontece com o placar?
- Em `DrawTriangle`, os vértices vão em sentido anti-horário. Inverta a ordem e veja o triângulo sumir.

### Passo 3 — Teclado e mouse · [`mover.c`](mover.c)

**Resultado esperado**: o quadrado anda com as setas, troca de cor **uma vez** a cada toque no espaço e pula para onde você clica. As coordenadas aparecem no canto.

**Experimente**: troque `IsKeyPressed(KEY_SPACE)` por `IsKeyDown(KEY_SPACE)` e segure o espaço. Qual a diferença entre as duas funções?

> Lembre: na tela, **y cresce para baixo**. Por isso a seta para cima *subtrai* de `y`.

### Passo 4 — Bola que quica com delta time · [`bola.c`](bola.c)

A velocidade está em **pixels por segundo** e é multiplicada por `GetFrameTime()` a cada quadro.

**Resultado esperado**: bola vermelha quicando nas quatro bordas e o FPS no canto, perto de 60.

**Experimente**:
1. Mude `SetTargetFPS(60)` para `SetTargetFPS(20)`. A animação fica travada, mas a bola atravessa a tela no mesmo tempo.
2. Agora tire o `* dt` e repita. O que muda?

### Passo 5 — Pong completo · [`pong.c`](pong.c)

| Jogador | Sobe | Desce |
| --- | --- | --- |
| 1 (esquerda) | **W** | **S** |
| 2 (direita) | **↑** | **↓** |

**Resultado esperado**: quadra preta, duas raquetes brancas, bola vermelha e placar. Jogue uma partida até 5 com o colega.

> Este Pong tem uma correção em relação ao slide: a bola só inverte na raquete se estiver indo na direção dela (`&& bola.vel.x < 0`). Sem isso, a colisão dura vários quadros, a velocidade inverte em cada um e a bola "gruda" na raquete.

### Passo 6 — Laboratório: modifique o Pong

Copie o Pong para outro arquivo e faça **uma modificação por vez**, rodando depois de cada uma:

```bash
# [Windows] e [WSL]: o comando é o mesmo
cp pong.c pong_lab.c
make pong_lab
```

- [ ] **1.** Mude a cor da bola e do fundo da quadra.
- [ ] **2.** Faça a bola acelerar 10% a cada rebatida. *Dica: multiplique `bola.vel.x` por `1.1f` no mesmo `if` da colisão.*
- [ ] **3.** Impeça as raquetes de saírem da tela: `y` entre `0` e `ALTURA - rec.height`.
- [ ] **4.** Mostre "Ponto!" por 1 segundo quando alguém pontua. *Dica: uma variável `float tempoMsg` que recebe `1.0f` no ponto e diminui `dt` a cada quadro. Desenhe o texto enquanto ela for maior que zero.*

**Avaliação**: cada modificação funcionando e o código ainda legível.

---

## 4. Solução de problemas

| Sintoma ou mensagem | Ambiente | Solução |
| --- | --- | --- |
| `gcc: command not found` ou `'gcc' não é reconhecido` | Windows | Você está no cmd ou no PowerShell. Abra `C:\raylib\w64devkit\w64devkit.exe` |
| `raylib.h: No such file or directory` | Windows | Use o Makefile ou o comando completo com `-IC:/raylib/raylib/src` |
| `raylib.h: No such file or directory` | WSL | Faltou `sudo make install` em `~/raylib/src` |
| `undefined reference to 'InitWindow'` | Ambos | Faltou `-lraylib`, ou ele veio antes do `.c` |
| `undefined reference to 'timeBeginPeriod'` ou `'CreateDCW'` | Windows | Faltou `-lwinmm` ou `-lgdi32`. Use o comando completo |
| `cannot open output file pong.exe: Permission denied` | Windows | O jogo ainda está aberto. Feche a janela e compile de novo |
| O `.exe` some ou o antivírus avisa | Windows | Adicione a pasta do repositório às exceções do Windows Defender |
| `Makefile: *** missing separator` | Ambos | Há espaços onde deveria haver TAB antes do comando |
| `GL/gl.h: No such file` ao compilar a Raylib | WSL | Rode de novo o `sudo apt install` do Caminho B |
| `GLFW: Failed to initialize GLFW` ou `Failed to open display` | WSL | WSL 1 ou WSL sem WSLg. No PowerShell: `wsl --update`, `wsl --shutdown`. Windows 10 antigo: use o Caminho A |
| Janela preta, lenta ou erro de OpenGL | WSL | Atualize o driver de vídeo no Windows. Paliativo: `LIBGL_ALWAYS_SOFTWARE=1 ./pong` |
| `ALSA lib ... cannot find card` | WSL | Aviso de áudio. Pode ignorar |
| O jogo fica mais rápido em um PC do que em outro | Ambos | Multiplique toda velocidade por `GetFrameTime()` |
| Placar ou objeto não aparece | Ambos | Desenhe o fundo primeiro e a interface por último, tudo entre `BeginDrawing` e `EndDrawing` |

---

## 5. Referências

- [Site oficial da Raylib](https://www.raylib.com/)
- [Cheatsheet com todas as funções](https://www.raylib.com/cheatsheet/cheatsheet.html): deixe aberta numa aba enquanto programa
- [Exemplos oficiais](https://www.raylib.com/examples.html), com código-fonte de cada um
- [Instalador oficial para Windows](https://raysan5.itch.io/raylib)
- [Wiki: Working on Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows)
- [Wiki: Working on GNU Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux), base do Caminho B
- [Apps gráficos no WSL (Microsoft)](https://learn.microsoft.com/windows/wsl/tutorials/gui-apps)
