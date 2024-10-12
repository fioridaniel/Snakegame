#include "snakegame.h"

void drawTable(char tab[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            mvaddch(i, j, tab[i][j]);
        }
    }
    refresh(); 
}

void initializeTable(char tab[ROWS][COLS])
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            if(i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1)
            {
                tab[i][j] = '#';
            }
            else
            {
                tab[i][j] = '.';
            }
        }
    }
}

void delay(int milliseconds) 
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds * (CLOCKS_PER_SEC / 1000));
}

void generateTarget(char tab[ROWS][COLS], int *px, int *py)
{
    int tx, ty;
    do
    {
        tx = rand() % (ROWS - 2) + 1; 
        ty = rand() % (COLS - 2) + 1;
    } while (tab[tx][ty] != '.');
    *px = tx;
    *py = ty;
    tab[tx][ty] = '@';
}

void moveSnake(char tab[ROWS][COLS], Lista* l, int x, int y) {
    Node* aux = l->head; // começando pela cauda
    tab[aux->x][aux->y] = '.'; // limpa a posicao anterior da cauda

    while(aux->next != NULL) {
        aux->x = aux->next->x;
        aux->y = aux->next->y;
        aux = aux->next;
    }

    // atualiza a cabeca da cobra
    l->tail->x = x;
    l->tail->y = y;
}

void drawSnake(char tab[ROWS][COLS], Lista* l) {
    Node* t = l->tail;
    Node* aux = t->prev;

    if(t != NULL) {
        tab[t->x][t->y] = HEAD;
    }
    
    while(aux != NULL) {
        tab[aux->x][aux->y] = 'o';
        aux = aux->prev;
    }
}