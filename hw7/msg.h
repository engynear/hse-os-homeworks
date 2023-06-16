#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>

#define PERMISSIONS 0666

#define MESSAGE_TYPE_EMPTY 0
#define MESSAGE_TYPE_STRING 1
#define MESSAGE_TYPE_FINISH 2
#define MAX_STRING_LENGTH 120

typedef struct
{
    int type;
    char string[MAX_STRING_LENGTH];
} Message;