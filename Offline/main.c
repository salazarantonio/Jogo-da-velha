#include <stdio.h>
#include "def.h"

int main(void) {
    int tabuleiro[3][3], player, vencedor, linha, coluna, jogadaValida, estadoJogo = 1; // 1 ativo, 0 inativo

    printf("Voce e' o jogador 1 - X.");

    // Criar tabuleiro
    inicializar(tabuleiro);
    player = 4;

    while (estadoJogo) {
        mostrarT(tabuleiro);
        // Realizar a jogada
        do {
            if (player == 4) {
                printf("Vez de player %c\n", player == 4 ? 'X' : 'O');
                printf("Digite a linha e coluna de 0-2 para jogar: \n");
                scanf("%d %d", &linha, &coluna);
                jogadaValida = realizarJogada(tabuleiro, linha, coluna, player);
            }
            else {
                jogadaValida = jogadaIA(tabuleiro, player);
            }

            if (!jogadaValida) {
                printf("Posicao invalida! Digite novamente.\n\n");
            }
        } while (!jogadaValida);

        // Verificar se o jogador venceu
        vencedor = vitoria(tabuleiro);
        if (vencedor) {
            mostrarT(tabuleiro);
            printf("Jogador %c venceu!\n", vencedor == 1 ? 'O' : 'X');
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

        player = trocarP(player);
    }
    return 0;
}