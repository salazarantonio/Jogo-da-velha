#ifndef _def_H_
#define _def_H_

void inicializar(char tabuleiro[3][3]);
void mostrarT(char tabuleiro[3][3]);
int realizarJogada(char tabuleiro[3][3], int linha, int coluna, char player);
int vitoria(char tabuleiro[3][3], char player);
int empate(char tabuleiro[3][3]);
char trocarP(char player);

#endif