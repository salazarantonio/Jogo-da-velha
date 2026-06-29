#include <stdio.h>
#include "names.h"

int i = 0, j = 0;

void inicializar(char tabuleiro[3][3]) {
    for (i; i < 3; i++) {
        for (j; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarT(char tabuleiro[3][3]) {
    printf("   Col 0    Col 1    Col 2\n");
    printf("        |        |        |\n");
    for (i; i < 3; i++) {
        printf("Lin %d  %c  |   %c   |  %c   \n", i, tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);

        if (i < 2) {
            printf("   ------|-------|------\n");
        }
    }
}

int realizarJogada(char tabuleiro[3][3], int linha, int coluna, char player) {
    // Espaço vazio
    if (tabuleiro[linha][coluna] != ' ') {
        return 0;
    }

    // Posição correta
    if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
        return 0;
    }

    // Jogada validada
    tabuleiro[linha][coluna] = player;
    return 1;
}

int vitoria(char tabuleiro[3][3], char player) {
    // Horizontal
    

    // Vertical


    // Diagonal


    return 0;
}