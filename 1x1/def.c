#include <stdio.h>
#include "def.h"

void inicializar(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void mostrarT(char tabuleiro[3][3]) {
    printf("     Col 0 | Col 1 | Col 2\n");
    printf("     ------+-------+------\n");
    for (int i = 0; i < 3; i++) {
        printf("Lin %d   %c  |   %c   |  %c\n", i, tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i < 2) {
            printf("     ------+-------+------\n");
        }
    }
    printf("\n");
}

int realizarJogada(char tabuleiro[3][3], int linha, int coluna, char player) {
    // Verifica posição ocupada
    if (tabuleiro[linha][coluna] != ' ') {
        return 0;
    }

    // Verifica se está na posição correta
    if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
        return 0;
    }
    // Jogada validada
    tabuleiro[linha][coluna] = player;
    return 1;
}

int vitoria(char tabuleiro[3][3], char player) {
    int i;

    // Vertical
    for (i = 0; i < 3; i++) {
        if (tabuleiro[0][i] == player && tabuleiro[1][i] == player && tabuleiro[2][i] == player) {
            return 1;
        }
    }

    // Horizontal
    for (i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == player && tabuleiro[i][1] == player && tabuleiro[i][2] == player) {
            return 1;
        }
    }

    // Diagonal 1
    if (tabuleiro[0][0] == player && tabuleiro[1][1] == player && tabuleiro[2][2] == player) {
        return 1;
    }

    // Diagonal 2
    if (tabuleiro[0][2] == player && tabuleiro[1][1] == player && tabuleiro[2][0] == player) {
        return 1;
    }

    // Ninguem ganhou
    return 0;
}

int empate(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') {
                // Não empatou
                return 0;
            }
        }
    }
    // Empatou
    return 1;
}

char trocarP(char player) {
    if (player == 'X') {
        return 'O';
    }
    return 'X';
}