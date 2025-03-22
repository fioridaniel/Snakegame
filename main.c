#include "snakegame.h"

void initializeWindow() 
{
    initscr();            // Inicia a tela
    raw();                // Modo raw, captura a tecla sem buffer
    keypad(stdscr, TRUE); // Habilita captura de teclas especiais, como F1, setas, etc.
    noecho();             // Não exibe teclas pressionadas no terminal
    mvprintw(2, COLS + 5, "Pontuacao recorde: %d\n", lerPontuacaoRecorde());
}

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
    int headIndex[2] = {MIDR, MIDC + 3};
    int tailIndex[2] = {MIDR, MIDC};
    initializeSnake(lista, tab);

    // inicializa janela
    initializeWindow();

    int score = 0;
    int userInput;
    int direction = 'd'; // primeira direcao vai ser d para evitar erro

    // loop do jogo
    nodelay(stdscr, TRUE); 
    while(OnGame) 
    {
        userInput = getch();

        // caso input seja 'e' 
        if(userInput == 'e')
        {
            break;
        }

        // caso input seja 'esc'
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

        // caso input seja diferente de alguma tecla valida, o input permanece igual o ultimo input valido
        else if(userInput == ERR || userInput != 'w' && userInput != 'a' && userInput != 's' && userInput != 'd' && userInput != KEY_UP && userInput != KEY_LEFT && userInput != KEY_DOWN && userInput != KEY_RIGHT)
        {
           userInput = direction;
        }

        getUserInput(headIndex, userInput, direction);

        // caso a snake tenha "se comido", o jogo acaba
        if(tab[headIndex[0]][headIndex[1]] == 'o') goto endgame;

        foodWasEaten(lista, tab, headIndex, tailIndex, &tx, &ty, &score);

        // caso a snake tenha encostado em alguma borda do tabuleiro, o jogo acaba tambem
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