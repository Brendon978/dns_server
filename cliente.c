// cliente.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5050
#define MESSAGE "teste3.0"

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    // Cria o socket UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Falha ao criar o socket");
        exit(EXIT_FAILURE);
    }

    // Configura o endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // IP local
    server_addr.sin_port = htons(PORT);

    // Envia a mensagem ao servidor
    if (sendto(sockfd, MESSAGE, strlen(MESSAGE), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Falha ao enviar dados");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Mensagem enviada ao servidor\n");

    // Fecha o socket quando terminar
    close(sockfd);
    return 0;
}
