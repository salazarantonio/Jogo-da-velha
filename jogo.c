#include <stdio.h>
#include <string.h>
#include "jogo.h"

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
    if (tabuleiro[linha][coluna] != ' ') {
        return 0;
    }

    if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
        return 0;
    }

    tabuleiro[linha][coluna] = player;
    return 1;
}

int vitoria(char tabuleiro[3][3], char player) {
    int i;

    for (i = 0; i < 3; i++) {
        if (tabuleiro[0][i] == player && tabuleiro[1][i] == player && tabuleiro[2][i] == player) {
            return 1;
        }
    }

    for (i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == player && tabuleiro[i][1] == player && tabuleiro[i][2] == player) {
            return 1;
        }
    }

    if (tabuleiro[0][0] == player && tabuleiro[1][1] == player && tabuleiro[2][2] == player) {
        return 1;
    }

    if (tabuleiro[0][2] == player && tabuleiro[1][1] == player && tabuleiro[2][0] == player) {
        return 1;
    }

    return 0;
}

int empate(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

char trocarP(char player) {
    if (player == 'X') {
        return 'O';
    }
    return 'X';
}

void tabuleiroParaTexto(char tabuleiro[3][3], char destino[TAM_MENSAGEM]) {
    snprintf(
        destino,
        TAM_MENSAGEM,
        "     Col 0 | Col 1 | Col 2\n"
        "     ------+-------+------\n"
        "Lin 0   %c  |   %c   |  %c\n"
        "     ------+-------+------\n"
        "Lin 1   %c  |   %c   |  %c\n"
        "     ------+-------+------\n"
        "Lin 2   %c  |   %c   |  %c\n",
        tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2],
        tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2],
        tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]
    );
}

int coordenadaValida(int linha, int coluna) {
    return linha >= 0 && linha <= 2 && coluna >= 0 && coluna <= 2;
}
