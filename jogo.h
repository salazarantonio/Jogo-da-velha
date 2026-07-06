#ifndef JOGO_H
#define JOGO_H

#define TAM_MENSAGEM 2048

void inicializar(char tabuleiro[3][3]);
void mostrarT(char tabuleiro[3][3]);
int realizarJogada(char tabuleiro[3][3], int linha, int coluna, char player);
int vitoria(char tabuleiro[3][3], char player);
int empate(char tabuleiro[3][3]);
char trocarP(char player);

void tabuleiroParaTexto(char tabuleiro[3][3], char destino[TAM_MENSAGEM]);
int coordenadaValida(int linha, int coluna);

#endif
