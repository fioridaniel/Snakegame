#include "snakegame.h"

int main()
{
    srand(time(NULL));

    char tab[ROWS][COLS];
    gamestart:
    initializeTable(tab);
    
    // alvo da cobrinha
    int tx, ty;
    generateTarget(tab, &tx, &ty);

    // inicializando a lista
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if(lista == NULL)
    {
        return 1;
    }
    inicializaLista(lista);

    // inicializando a snake
    tab[MIDR][MIDC] = 'o'; tab[MIDR][MIDC + 1] = 'o'; tab[MIDR][MIDC + 2] = 'o'; tab[MIDR][MIDC + 3] = HEAD;
    int headIndex[2] = {MIDR, MIDC + 3};
    int tailIndex[2] = {MIDR, MIDC};

    insereInicio(lista, MIDR, MIDC + 3);
    insereInicio(lista, MIDR, MIDC + 2);
    insereInicio(lista, MIDR, MIDC + 1);
    insereInicio(lista, MIDR, MIDC);

    initscr();            // Inicia a tela
    raw();                // Modo raw, captura a tecla sem buffer
    keypad(stdscr, TRUE); // Habilita captura de teclas especiais, como F1, setas, etc.
    noecho();             // Não exibe teclas pressionadas no terminal
    mvprintw(2, COLS + 5, "Pontuacao recorde: %d\n", lerPontuacaoRecorde());

    int score = 0;
    int userInput;
    int direction = 'd'; // primeira direcao vai ser d para evitar erro

    nodelay(stdscr, TRUE); 
    while(OnGame) 
    {
        userInput = getch();

        if(userInput == 'e')
        {
            break;
        }

        if(userInput == KEY_ESC)
        {
            mvprintw(MIDR + 1, COLS + 5, "JOGO PAUSADO.\n");
            mvprintw(MIDR + 2, COLS + 5, "Pressione 'esc' novamente para voltar ao jogo.\n");
            do
            {
                userInput = getch();
            } while (userInput != KEY_ESC);
            clear();
            refresh();
            userInput = direction;
        }

        else if(userInput == ERR || userInput != 'w' && userInput != 'a' && userInput != 's' && userInput != 'd' && userInput != KEY_UP && userInput != KEY_LEFT && userInput != KEY_DOWN && userInput != KEY_RIGHT)
        {
           userInput = direction;
        }
       
        if(userInput == 'w' || userInput == KEY_UP) // mover a snake para cima
        {
            if(direction == 's' || direction == KEY_DOWN) continue; 
            headIndex[0]--;   
        }

        else if(userInput == 'a' || userInput == KEY_LEFT) // mover a snake para esquerda
        {
            if(direction == 'd' || direction == KEY_RIGHT) continue;
            headIndex[1]--;      
        }

        else if(userInput == 's' || userInput == KEY_DOWN) // mover para baixo
        {
            if(direction == 'w' || direction == KEY_UP) continue;
            headIndex[0]++;
        }

        else if(userInput == 'd' || userInput == KEY_RIGHT) // mover para a direita
        {
            if(direction == 'a' || direction == KEY_LEFT) continue;
            headIndex[1]++;
        }

        if(tab[headIndex[0]][headIndex[1]] == 'o') goto endgame;

        if(headIndex[0] == tx && headIndex[1] == ty) // logica para ver se a comida foi achada
        {
            tab[tx][ty] = '.';

            generateTarget(tab, &tx, &ty);

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
            score++;
            
            if(salvarPontuacaoRecorde(score))
            {
                mvprintw(2, COLS + 5, "Pontuacao recorde: %d\n", lerPontuacaoRecorde());
            }
        }

        if(headIndex[0] == ROWS - 1 || headIndex[0] == 0 || headIndex[1] == COLS - 1 || headIndex[1] == 0)
        {
            endgame:
            //clear();
            mvprintw(MIDR, COLS + 5, "VOCE PERDEU\n");
            mvprintw(MIDR + 1, COLS + 5, "Pressione 'e' ou 'esc' para sair, ou pressione qualquer botao para recomecar.\n");
            refresh();
            sleep(3);

            while(true)
            { 
                userInput = getch();
                if(userInput == KEY_ESC || userInput == 'e')
                {
                    break;
                }
                
                else if(userInput != ERR)
                {
                    clear();
                    liberaLista(lista);
                    goto gamestart;
                }
            }
            clear();
            refresh();
            break;
        }

        direction = userInput;
        moveSnake(tab, lista, headIndex[0], headIndex[1]);
        drawSnake(tab, lista);
        drawTable(tab);
        mvprintw(ROWS, 0, "PONTUACAO: %d", score); // mover o cursor para a linha de baixo do tabuleiro e mostrar o score
        refresh(); 
        delay(DELAY);
    }

    endwin();   
    return 0;
}