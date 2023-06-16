#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

#include "msg.h"

const char *shared_object = "posix-shared-object";

void printError(char *msg)
{
    puts(msg);
    exit(1);
}

int main()
{
    int shared_memory_id;
    Message *message_pointer;
    char message_content[MAX_STRING_LENGTH];
    if ((shared_memory_id = shm_open(shared_object, O_CREAT | O_RDWR, PERMISSIONS)) == -1)
    {
        perror("shm_open");
        printError("server: the object is already open");
    }
    else
    {
        printf("Object is open: name = %s, id = 0x%x\n", shared_object, shared_memory_id);
    }

    if (ftruncate(shared_memory_id, sizeof(Message)) == -1)
    {
        perror("ftruncate");
        printError("server: memory sizing error");
        return 1;
    }
    else
    {
        printf("Memory size set and = %lu\n", sizeof(Message));
    }

    message_pointer = (Message *)mmap(0, sizeof(Message), PROT_WRITE | PROT_READ, MAP_SHARED,
                                      shared_memory_id, 0);
    if (message_pointer == (Message *)-1)
    {
        printError("server: error getting pointer to shared memory");
    }

    message_pointer->type = MESSAGE_TYPE_EMPTY;

    while (1)
    {
        if (message_pointer->type != MESSAGE_TYPE_EMPTY)
        {
            if (message_pointer->type == MESSAGE_TYPE_STRING)
            {
                printf("%s\n", message_pointer->string);
            }
            else if (message_pointer->type == MESSAGE_TYPE_FINISH)
            {
                break;
            }
            message_pointer->type = MESSAGE_TYPE_EMPTY;
        }
    }

    if (shm_unlink(shared_object) == -1)
    {
        perror("shm_unlink");
        printError("server: error removing shared memory object");
    }

    return 0;
}