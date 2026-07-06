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

#define PORTA 8080
#define TAM_BUFFER 2048

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

int comecaCom(const char *texto, const char *prefixo) {
    return strncmp(texto, prefixo, strlen(prefixo)) == 0;
}

const char *conteudoMensagem(const char *buffer) {
    const char *quebra = strchr(buffer, '\n');

    if (quebra == NULL) {
        return buffer;
    }

    return quebra + 1;
}

int main() {
    socket_tipo sock;
    struct sockaddr_in servidor;
    char buffer[TAM_BUFFER];
    char entrada[TAM_BUFFER];

    if (iniciar_rede() != 0) {
        printf("Erro ao iniciar a rede.\n");
        exit(EXIT_FAILURE);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        perror("Erro ao criar socket");
        finalizar_rede();
        exit(EXIT_FAILURE);
    }

    servidor.sin_family = AF_INET;
    servidor.sin_port = htons(PORTA);

#ifdef _WIN32
    servidor.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (servidor.sin_addr.s_addr == INADDR_NONE) {
#else
    if (inet_pton(AF_INET, "127.0.0.1", &servidor.sin_addr) <= 0) {
#endif
        perror("Endereco invalido");
        fechar_socket(sock);
        finalizar_rede();
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&servidor, sizeof(servidor)) < 0) {
        perror("Erro ao conectar");
        fechar_socket(sock);
        finalizar_rede();
        exit(EXIT_FAILURE);
    }

    printf("Conectado ao servidor!\n");
    printf("Voce e o Jogador 2 (O).\n\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) {
            printf("Servidor desconectou.\n");
            break;
        }

        printf("%s\n", conteudoMensagem(buffer));

        if (comecaCom(buffer, "FIM")) {
            break;
        }

        if (comecaCom(buffer, "SUA_VEZ")) {
            printf("Jogador 2 (O), digite linha e coluna de 0 a 2: ");

            if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
                strcpy(entrada, "sair");
            }

            entrada[strcspn(entrada, "\n")] = '\0';
            send(sock, entrada, strlen(entrada) + 1, 0);
        }
    }

    fechar_socket(sock);
    finalizar_rede();

    return 0;
}
