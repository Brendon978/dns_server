//emilly<3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 5050
#define BUFFER_SIZE 1024

int sockfd;
FILE *file;

void cleanup() {
    if (file) {
        fclose(file);
    }
    if (sockfd >= 0) {
        close(sockfd);
    }
    exit(0);
}

void handle_signal(int signal) {
    cleanup();
}

int main() {
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_len = sizeof(client_addr);

    // Configura o tratamento de sinal para garantir o fechamento adequado
    signal(SIGINT, handle_signal);

    // Cria o socket UDP
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Falha ao criar o socket");
        exit(EXIT_FAILURE);
    }

    // Configura o endereço do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Liga o socket ao endereço e porta
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Falha ao ligar o socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Servidor escutando na porta %d...\n", PORT);

    // Abre o arquivo para armazenar as mensagens recebidas
    file = fopen("requisicoes.txt", "a");
    if (file == NULL) {
        perror("Falha ao abrir o arquivo");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Recebe dados do cliente
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr*)&client_addr, &addr_len);
        if (n < 0) {
            perror("Falha ao receber dados");
            continue;
        }
        buffer[n] = '\0';  // Garante que a string está terminada

        // Exibe a mensagem recebida no console
        printf("Recebido: %s\n", buffer);

        // Armazena a mensagem recebida no arquivo
        fprintf(file, "Mensagem recebida: %s\n", buffer);
        fflush(file);  // Garante que a mensagem é gravada no arquivo imediatamente
    }

    // Fecha o arquivo e o socket quando terminar
    cleanup();
    return 0;
}
