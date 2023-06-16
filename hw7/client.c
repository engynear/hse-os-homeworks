#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include "msg.h"

const char *shared_object = "posix-shared-object";

void printError(char *msg)
{
    puts(msg);
    exit(1);
}

int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min);
}

char *intToString(int number)
{
    char *string = (char *)malloc(sizeof(char) * 10);
    sprintf(string, "%d", number);
    return string;
}

int main(int argc, char *argv[])
{
    int shared_memory_id, number_to_send, number_of_sends, current_send = 0;
    Message *message_to_send;
    char *message_content;
    srand(time(NULL));

    if (argc == 2)
    {
        number_of_sends = atoi(argv[1]);
    }
    else
    {
        printf("Вы не указали количество отправок. По умолчанию будет 10\n");
        number_of_sends = 10;
    }

    if ((shared_memory_id = shm_open(shared_object, O_CREAT | O_RDWR, PERMISSIONS)) == -1)
    {
        perror("shm_open");
        printError("client: объект уже открыт");
    }
    else
    {
        printf("Объект открыт: имя = %s, идентификатор = 0x%x\n", shared_object, shared_memory_id);
    }

    message_to_send = (Message *)mmap(0, sizeof(Message), PROT_WRITE | PROT_READ, MAP_SHARED,
                                      shared_memory_id, 0);
    if (message_to_send == (Message *)-1)
    {
        perror("mmap");
        printError("client: не удалось получить разделяемую память");
    }

    while (1)
    {
        if (current_send == number_of_sends)
        {
            message_to_send->type = MESSAGE_TYPE_FINISH;
            strncpy(message_to_send->string, message_content, MAX_STRING_LENGTH);
            break;
        }

        message_content = intToString(getRandomNumber(0, 1000));
        int len = strlen(message_content);
        message_content[len - 1] = '\n';
        printf("Отправка: %s \n", message_content);

        message_to_send->type = MESSAGE_TYPE_STRING;
        strncpy(message_to_send->string, message_content, MAX_STRING_LENGTH);

        current_send++;
        sleep(1);
    }

    close(shared_memory_id);
    return 0;
}
