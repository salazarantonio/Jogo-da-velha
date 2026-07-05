#include <stdio.h>
#include "def.h"

void inicializar(int tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

void mostrarT(int tabuleiro[3][3]) {
    printf("\033[2J\033[H");

    char c;
    printf("     Col 0 | Col 1 | Col 2\n");
    printf("     ------+-------+------\n");
    for (int i = 0; i < 3; i++) {
        printf("Lin %d   ", i);
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == 0) c = ' ';
            else if (tabuleiro[i][j] == 1) c = 'O';
            else c = 'X';

            printf("%c", c);
            if (j < 2) printf("  |   ");
        }
        printf("\n");
        if (i < 2) {
            printf("     ------+-------+------\n");
        }
    }
    printf("\n");
}

int realizarJogada(int tabuleiro[3][3], int linha, int coluna, int player) {
    // Verifica se está na posição correta
    if (linha < 0 || linha > 2 || coluna < 0 || coluna > 2) {
        return 0;
    }

    // Verifica posição ocupada
    if (tabuleiro[linha][coluna] != 0) {
        return 0;
    }

    // Jogada validada
    tabuleiro[linha][coluna] = player;
    return 1;
}

int jogadaIA(int tabuleiro[3][3], int player) {
    int i, j, k, z, linha, coluna, ocupado, vazio, lVazio, cVazio;
    int X = trocarP(player);
    int combinacoes[8][3][2] = {
        {{0, 0}, {0, 1}, {0, 2}},
        {{1, 0}, {1, 1}, {1, 2}},
        {{2, 0}, {2, 1}, {2, 2}},
        {{0, 0}, {1, 0}, {2, 0}},
        {{0, 1}, {1, 1}, {2, 1}},
        {{0, 2}, {1, 2}, {2, 2}},
        {{0, 0}, {1, 1}, {2, 2}},
        {{2, 0}, {1, 1}, {0, 2}}
    };

    // R1 - vencer
    for (i = 0; i < 8; i++) {
        ocupado = 0, vazio = 0, lVazio = -1, cVazio = -1; // -1 simbolico
        for (j = 0; j < 3; j++) {
            linha = combinacoes[i][j][0];
            coluna = combinacoes[i][j][1];
            if (tabuleiro[linha][coluna] == player) {
                ocupado++;
            } else if (tabuleiro[linha][coluna] == 0) {
                vazio++;
                lVazio = linha, cVazio = coluna;
            }
        }
        // Joga na posicao vazia pra realizar combinacao
        if (ocupado == 2 && vazio == 1) {
            return realizarJogada(tabuleiro, lVazio, cVazio, player);
        }
    }

    // R1 - fechar adversario
    for (i= 0; i < 8; i++) {
        ocupado = 0, vazio = 0, lVazio = -1, cVazio = -1;
        for (j = 0; j < 3; j++) {
            linha = combinacoes[i][j][0];
            coluna = combinacoes[i][j][1];
            if (tabuleiro[linha][coluna] == X) {
                ocupado++;
            } else if (tabuleiro[linha][coluna] == 0) {
                vazio++;
                lVazio = linha, cVazio = coluna;
            }
        }
        if (ocupado == 2 && vazio == 1) {
            return realizarJogada(tabuleiro, lVazio, cVazio, player);
        }
    }

    // R2 criar combinacao
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            // Se ocupado, procurar outra posicao, senao jogar
            if (tabuleiro[i][j] != 0) {
                continue;
            }

            // Verificar jogadas possiveis nas combinacoes
            tabuleiro[i][j] = player;
            int jogadas = 0;
            for (k = 0; k < 8; k++) {
                ocupado = 0, vazio = 0;
                for (z = 0; z < 3; z++) {
                    linha = combinacoes[k][z][0];
                    coluna = combinacoes[k][z][1];
                    if (tabuleiro[linha][coluna] == player) {
                        ocupado++;
                    } else if (tabuleiro[linha][coluna] == 0) {
                        vazio++;
                    }
                    if (ocupado == 2 && vazio == 1) {
                        jogadas++;
                    }
                }
                tabuleiro[i][j] = 0;
            }
            if (jogadas >= 2) {
                return realizarJogada(tabuleiro, i, j, player);
            }
        }
    }

    // R3 pos central
    if (tabuleiro[1][1] == 0) {
        return realizarJogada(tabuleiro, 1, 1, player);
    }

    // R4 marcar canto oposto
    int cantos[4][2] = {
        {0, 0}, // 0- esquerda cima
        {0, 2}, // 1- direita cima
        {2, 0}, // 2- esqueda baixo
        {2, 2} // 3- direita baixo
    };
    int opostos[4] = {3, 2, 1, 0};
    for (i = 0; i < 4; i++) {
        linha = cantos[i][0];
        coluna = cantos[i][1];
        if (tabuleiro[linha][coluna] == X) {
            linha = cantos[opostos[i]][0];
            coluna = cantos[opostos[i]][1];
            if (tabuleiro[linha][coluna] == 0) {
                return realizarJogada(tabuleiro, linha, coluna, player);
            }
        }
    }

    // R5 marcar canto vazio
    for (i = 0; i < 4; i++) {
        linha = cantos[i][0];
        coluna = cantos[i][1];
        if (tabuleiro[linha][coluna] == 0) {
            return realizarJogada(tabuleiro, linha, coluna, player);
        }
    }

    // R6 marcar vazio
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == 0) {
                return realizarJogada(tabuleiro, i, j, player);
            }
        }
    }
}

int vitoria(int tabuleiro[3][3]) {
    int i, soma;

    // Vertical
    for (i = 0; i < 3; i++) {
        soma = tabuleiro[0][i] + tabuleiro[1][i] + tabuleiro[2][i];
        if (soma == 3) return 1;
        if (soma == 12) return 4;
    }

    // Horizontal
    for (i = 0; i < 3; i++) {
        soma = tabuleiro[i][0] + tabuleiro[i][1] + tabuleiro[i][2];
        if (soma == 3) return 1;
        if (soma == 12) return 4;
    }

    // Diagonal 1
    soma = tabuleiro[0][0] + tabuleiro[1][1] + tabuleiro[2][2];
    if (soma == 3) return 1;
    if (soma == 12) return 4;

    // Diagonal 2
    soma = tabuleiro[0][2] + tabuleiro[1][1] + tabuleiro[2][0];
    if (soma == 3) return 1;
    if (soma == 12) return 4;

    // Ninguem ganhou
    return 0;
}

int empate(int tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[i][j] == 0) {
                // Não empatou
                return 0;
            }
        }
    }
    // Empatou
    return 1;
}

int trocarP(int player) {
    if (player == 4) {
        return 1;
    }
    return 4;
}