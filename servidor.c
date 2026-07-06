#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <unistd.h>
#include <arpa/inet.h>
#endif

#include "jogo.h"

#define PORTA 8080
#define TAM_BUFFER 1024

#ifdef _WIN32
typedef SOCKET socket_tipo;
#define fechar_socket closesocket
#else
typedef int socket_tipo;
#define fechar_socket close
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#endif

int iniciar_rede() {
#ifdef _WIN32
    WSADATA wsa;
    return WSAStartup(MAKEWORD(2, 2), &wsa);
#else
    return 0;
#endif
}

void finalizar_rede() {
#ifdef _WIN32
    WSACleanup();
#endif
}

void enviarMensagem(socket_tipo cliente_fd, const char *tipo, char tabuleiro[3][3], const char *texto) {
    char mensagem[TAM_MENSAGEM];
    char desenho[TAM_MENSAGEM];

    tabuleiroParaTexto(tabuleiro, desenho);
    snprintf(mensagem, sizeof(mensagem), "%s\n%s\n%s", tipo, texto, desenho);

    send(cliente_fd, mensagem, strlen(mensagem) + 1, 0);
}

int lerJogadaServidor(char tabuleiro[3][3]) {
    char entrada[TAM_BUFFER];
    int linha, coluna;

    while (1) {
        printf("Jogador 1 (X), digite linha e coluna de 0 a 2: ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            return 0;
        }

        if (sscanf(entrada, "%d %d", &linha, &coluna) != 2) {
            printf("Entrada invalida. Exemplo: 1 2\n\n");
            continue;
        }

        if (!coordenadaValida(linha, coluna)) {
            printf("Posicao invalida. Use valores entre 0 e 2.\n\n");
            continue;
        }

        if (!realizarJogada(tabuleiro, linha, coluna, 'X')) {
            printf("Posicao ocupada. Tente novamente.\n\n");
            continue;
        }

        return 1;
    }
}

int receberJogadaCliente(socket_tipo cliente_fd, char tabuleiro[3][3]) {
    char buffer[TAM_BUFFER];
    int linha, coluna;

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(cliente_fd, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            printf("Cliente desconectou.\n");
            return 0;
        }

        if (strcmp(buffer, "sair") == 0) {
            return 0;
        }

        if (sscanf(buffer, "%d %d", &linha, &coluna) != 2) {
            enviarMensagem(cliente_fd, "SUA_VEZ", tabuleiro, "Entrada invalida. Digite no formato: linha coluna");
            continue;
        }

        if (!coordenadaValida(linha, coluna)) {
            enviarMensagem(cliente_fd, "SUA_VEZ", tabuleiro, "Posicao invalida. Use valores entre 0 e 2.");
            continue;
        }

        if (!realizarJogada(tabuleiro, linha, coluna, 'O')) {
            enviarMensagem(cliente_fd, "SUA_VEZ", tabuleiro, "Posicao ocupada. Tente novamente.");
            continue;
        }

        printf("Jogador 2 (O) jogou em: %d %d\n\n", linha, coluna);
        return 1;
    }
}

int main() {
    socket_tipo servidor_fd, cliente_fd;
    struct sockaddr_in endereco;
#ifdef _WIN32
    int endereco_len = sizeof(endereco);
#else
    socklen_t endereco_len = sizeof(endereco);
#endif
    char tabuleiro[3][3];

    if (iniciar_rede() != 0) {
        printf("Erro ao iniciar a rede.\n");
        exit(EXIT_FAILURE);
    }

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (servidor_fd == INVALID_SOCKET) {
        perror("Erro ao criar socket");
        finalizar_rede();
        exit(EXIT_FAILURE);
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_port = htons(PORTA);

    if (bind(servidor_fd, (struct sockaddr *)&endereco, sizeof(endereco)) < 0) {
        perror("Erro no bind");
        fechar_socket(servidor_fd);
        finalizar_rede();
        exit(EXIT_FAILURE);
    }

    if (listen(servidor_fd, 1) < 0) {
        perror("Erro no listen");
        fechar_socket(servidor_fd);
        finalizar_rede();
        exit(EXIT_FAILURE);
    }

    printf("Servidor aguardando conexao na porta %d...\n", PORTA);

    cliente_fd = accept(servidor_fd, (struct sockaddr *)&endereco, &endereco_len);
    if (cliente_fd == INVALID_SOCKET) {
        perror("Erro no accept");
        fechar_socket(servidor_fd);
        finalizar_rede();
        exit(EXIT_FAILURE);
    }

    printf("Cliente conectado!\n");
    printf("Jogador 1: X (servidor)\n");
    printf("Jogador 2: O (cliente)\n\n");

    inicializar(tabuleiro);
    enviarMensagem(cliente_fd, "AGUARDE", tabuleiro, "Voce e o Jogador 2 (O). Aguarde a jogada do Jogador 1.");

    while (1) {
        mostrarT(tabuleiro);

        if (!lerJogadaServidor(tabuleiro)) {
            enviarMensagem(cliente_fd, "FIM", tabuleiro, "Servidor encerrou o jogo.");
            break;
        }

        if (vitoria(tabuleiro, 'X')) {
            mostrarT(tabuleiro);
            printf("Jogador 1 (X) venceu!\n");
            enviarMensagem(cliente_fd, "FIM", tabuleiro, "Jogador 1 (X) venceu!");
            break;
        }

        if (empate(tabuleiro)) {
            mostrarT(tabuleiro);
            printf("Ninguem ganhou. Empate!\n");
            enviarMensagem(cliente_fd, "FIM", tabuleiro, "Ninguem ganhou. Empate!");
            break;
        }

        enviarMensagem(cliente_fd, "SUA_VEZ", tabuleiro, "Sua vez, Jogador 2 (O).");

        if (!receberJogadaCliente(cliente_fd, tabuleiro)) {
            break;
        }

        if (vitoria(tabuleiro, 'O')) {
            mostrarT(tabuleiro);
            printf("Jogador 2 (O) venceu!\n");
            enviarMensagem(cliente_fd, "FIM", tabuleiro, "Jogador 2 (O) venceu!");
            break;
        }

        if (empate(tabuleiro)) {
            mostrarT(tabuleiro);
            printf("Ninguem ganhou. Empate!\n");
            enviarMensagem(cliente_fd, "FIM", tabuleiro, "Ninguem ganhou. Empate!");
            break;
        }

        enviarMensagem(cliente_fd, "AGUARDE", tabuleiro, "Jogada recebida. Aguarde o Jogador 1.");
    }

    fechar_socket(cliente_fd);
    fechar_socket(servidor_fd);
    finalizar_rede();

    return 0;
}
