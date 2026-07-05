#ifndef _def_H_
#define _def_H_

void inicializar(int tabuleiro[3][3]);
void mostrarT(int tabuleiro[3][3]);
int realizarJogada(int tabuleiro[3][3], int linha, int coluna, int player);
int jogadaIA(int tabuleiro[3][3], int player);
int vitoria(int tabuleiro[3][3]);
int empate(int tabuleiro[3][3]);
int trocarP(int player);

#endif