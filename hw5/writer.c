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
    char input[BUFFER_SIZE];

    mkfifo(FIFO_NAME, 0666);

    printf("Writer: Ожидание открытия именованного канала...\n");

    fd = open(FIFO_NAME, O_WRONLY);

    printf("Writer: Именованный канал открыт.\n");
    printf("Writer: Введите данные для передачи (\"exit\" для выхода):\n");

    while (1) {
        fgets(input, BUFFER_SIZE, stdin);

        write(fd, input, strlen(input) + 1);

        if (strcmp(input, "exit\n") == 0)
            break;
    }

    close(fd);

    unlink(FIFO_NAME);

    return 0;
}
