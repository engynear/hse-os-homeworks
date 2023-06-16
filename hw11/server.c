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

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[BUFFER_SIZE];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Ошибка вызова socket()");
        exit(1);
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIP);
    serverAddress.sin_port = htons(serverPort);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        perror("Ошибка вызова bind()");
        exit(1);
    }

    if (listen(serverSocket, 5) < 0) {
        perror("Ошибка вызова listen()");
        exit(1);
    }

    printf("Сервер запущен. Ожидание подключений...\n");

    while (1) {
        socklen_t clientAddressLength = sizeof(clientAddress);
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
        if (clientSocket < 0) {
            perror("Ошибка вызова accept()");
            exit(1);
        }

        printf("Клиент подключен: %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));

        while (1) {
            memset(buffer, 0, sizeof(buffer));
            int bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
            if (bytesRead < 0) {
                perror("Ошибка вызова recv()");
                exit(1);
            } else if (bytesRead == 0) {
                break;
            }

            printf("Получено от клиента %s:%d: %s\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port), buffer);

            if (strcmp(buffer, "The End") == 0) {
                break;
            }
        }

        close(clientSocket);
    }

    close(serverSocket);

    return 0;
}
