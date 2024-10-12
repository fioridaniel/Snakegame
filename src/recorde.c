#include <stdio.h>
#include "recorde.h"

#define RECORD_FILE "recorde.txt"

int lerPontuacaoRecorde() {
    FILE *file = fopen(RECORD_FILE, "r");
    if (!file) {
        return 0; // Se o arquivo não existir, a pontuação recorde é 0
    }

    int recorde;
    fscanf(file, "%d", &recorde);
    fclose(file);
    return recorde;
}

bool salvarPontuacaoRecorde(int score) {
    int pr = lerPontuacaoRecorde();

    if(score > pr)
    {
        FILE *file = fopen(RECORD_FILE, "w");
        if (file) {
            fprintf(file, "%d", score);
            fclose(file);
            return true;
        }
    }
    return false;
}