//emilly<3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Falha ao criar o socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(53);

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Falha ao ligar o socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor DNS rodando na porta 53...\n");

    while (1) {
        len = sizeof(client_addr);
        int n = recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&client_addr, &len);
        if (n < 0) {
            perror("Falha ao receber dados");
            continue;
        }

        printf("Recebida solicitação DNS\n");
    }

    close(sockfd);
    return 0;
}
