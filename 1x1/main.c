#include <stdio.h>
#include "def.h"

int main(void) {
    char tabuleiro[3][3], player;
    int linha, coluna, jogadaValida, estadoJogo = 1; // 1 ativo, 0 inativo

    printf("Player 1 - X, Player 2 - O\n\n");

    // Criar tabuleiro
    inicializar(tabuleiro);
    player = 'X';

    while (estadoJogo) {
        mostrarT(tabuleiro);

        // Realizar a jogada
        do {
            printf("Vez de player %c\n", player);
            printf("Digite a linha e coluna de 0-2 para jogar: \n");
            scanf("%d %d", &linha, &coluna);

            jogadaValida = realizarJogada(tabuleiro, linha, coluna, player);

            if (!jogadaValida) {
                printf("Posicao invalida! Digite novamente.\n\n");
            }
        } while (!jogadaValida);

        // Verificar se o jogador venceu
        if (vitoria(tabuleiro, player)) {
            mostrarT(tabuleiro);
            printf("Jogador %c venceu!\n", player);
            // Encerrar
            estadoJogo = 0;
        }
            
        // Verificar se o jogo empatou
        if (empate(tabuleiro)) {
            mostrarT(tabuleiro);
            printf("Ninguem ganhou. Empate!\n");
            // Encerrar
            estadoJogo = 0;
        }

        // Trocar player
        player = trocarP(player);
        
    }
    return 0;
}