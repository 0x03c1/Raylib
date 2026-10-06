# Makefile da Aula 18 - funciona no Windows (w64devkit), no WSL/Linux e no macOS
# Uso:  make            -> compila todos os .c da pasta
#       make desafio3   -> compila so o desafio3.c
#       make clean      -> apaga os executaveis

CC      = gcc
CFLAGS  = -Wall -std=c99
PROGS   = $(basename $(wildcard *.c))   # todo arquivo .c da pasta

ifeq ($(OS),Windows_NT)
    # Windows nativo: raylib instalada pelo instalador oficial em C:\raylib
    RAYLIB ?= C:/raylib/raylib/src
    CFLAGS += -I$(RAYLIB)
    LDLIBS  = -L$(RAYLIB) -lraylib -lopengl32 -lgdi32 -lwinmm -lshcore
else ifeq ($(shell uname -s),Darwin)
    # macOS (so o professor): brew install raylib
    CFLAGS += $(shell pkg-config --cflags raylib)
    LDLIBS  = $(shell pkg-config --libs raylib)
else
    # Linux / WSL: raylib compilada e instalada com sudo make install
    LDLIBS  = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(PROGS) *.exe

.PHONY: all clean
