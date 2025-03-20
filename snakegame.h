#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include "lista.h"
#include "recorde.h"

#define ROWS 33
#define COLS 41

#define MIDR (ROWS / 2)
#define MIDC (COLS / 2)

#define HEAD '$'
#define KEY_ESC 27
#define DELAY 100
#define OnGame true

void drawTable(char tab[ROWS][COLS]);

void initializeTable(char tab[ROWS][COLS]);

void delay(int milliseconds);

void generateTarget(char tab[ROWS][COLS], int *px, int *py);

void moveSnake(char tab[ROWS][COLS], Lista* l, int x, int y);

void getUserInput(int* headIndex, int userInput, int direction);

void foodWasEaten(Lista* lista, char tab[ROWS][COLS], int* headIndex, int* tailIndex, int tx, int ty, int score);

void drawSnake(char tab[ROWS][COLS], Lista* l);

#endif