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

void getUserInput(int* headIndex, int userInput, int direction) {
    if(userInput == 'w' || userInput == KEY_UP) // mover a snake para cima
    {
        if(direction == 's' || direction == KEY_DOWN) return;
        headIndex[0]--;   
    }

    else if(userInput == 'a' || userInput == KEY_LEFT) // mover a snake para esquerda
    {
        if(direction == 'd' || direction == KEY_RIGHT) return;
        headIndex[1]--;      
    }

    else if(userInput == 's' || userInput == KEY_DOWN) // mover para baixo
    {
        if(direction == 'w' || direction == KEY_UP) return;
        headIndex[0]++;
    }

    else if(userInput == 'd' || userInput == KEY_RIGHT) // mover para a direita
    {
        if(direction == 'a' || direction == KEY_LEFT) return; 
        headIndex[1]++;
    }
}

void foodWasEaten(Lista* lista, char tab[ROWS][COLS], int* headIndex, int* tailIndex, int* tx, int* ty, int* pscore) {
    if(headIndex[0] == tx && headIndex[1] == ty) // logica para ver se a comida foi achada
    {
        tab[*tx][*ty] = '.';

        generateTarget(tab, tx, ty); // mudar aqui, tx e ty serao ponteiros

        if(tab[tailIndex[0]][tailIndex[1] + 1] == 'o')
        {
            tailIndex[1]--;
        }

        else if(tab[tailIndex[0]][tailIndex[1] - 1] == 'o')
        {
            tailIndex[1]++;
        }

        else if(tab[tailIndex[0] + 1][tailIndex[1]] == 'o')
        {
            tailIndex[0]--;
        }
        
        else if(tab[tailIndex[0] - 1][tailIndex[1]] == 'o')
        {
            tailIndex[0]++;
        }

        insereInicio(lista, tailIndex[0], tailIndex[1]);
        *pscore++;
        
        if(salvarPontuacaoRecorde(*pscore))
        {
            mvprintw(2, COLS + 5, "Pontuacao recorde: %d\n", lerPontuacaoRecorde());
        }
    }
}