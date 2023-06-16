#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "DieWithError.h"

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <IP-адрес сервера> <Порт сервера>\n", argv[0]);
        exit(1);
    }

    char *serverIP = argv[1];
    int serverPort = atoi(argv[2]);

    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Ошибка вызова socket()");
        exit(1);
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);
    serverAddress.sin_port = htons(serverPort);

    if (connect(clientSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Ошибка вызова connect()");
        exit(1);
    }

    printf("Подключено к серверу. Ожидание сообщений от клиента 1...\n");

    while (1) {
        memset(buffer, 0, sizeof(buffer));

        int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead < 0) {
            perror("Ошибка вызова recv()");
            exit(1);
        } else if (bytesRead == 0) {
            break;
        }

        printf("Получено от сервера: %s\n", buffer);

        if (strcmp(buffer, "The End") == 0) {
            break;
        }
    }

    close(clientSocket);

    return 0;
}
