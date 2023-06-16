#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 256
#define FIFO_NAME "/tmp/myfifo"

int main()
{
    int fd;
    char buffer[BUFFER_SIZE];

    printf("Reader: Ожидание открытия именованного канала...\n");

    fd = open(FIFO_NAME, O_RDONLY);

    printf("Reader: Именованный канал открыт.\n");

    while (1) {
        read(fd, buffer, BUFFER_SIZE);

        if (buffer[0] != '\0') {
            printf("Reader: Получены данные: %s", buffer);

            for (int i = 0; buffer[i] != '\0'; i++) {
                if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                    buffer[i] = buffer[i] - 32;
                }
            }


            printf("Reader: Отправка ответа: %s", buffer);


            int responseFd = open(FIFO_NAME, O_WRONLY);
            write(responseFd, buffer, strlen(buffer) + 1);
            close(responseFd);
        }

        if (strstr(buffer, "EXIT") != NULL)
            break;
        memset(buffer, 0, BUFFER_SIZE);
    }

    close(fd);

    return 0;
}
