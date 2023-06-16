#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include "shared_memory.h"

extern struct shared_data *shared_data_ptr;

void signal_handler(int signum) {
    detach_shared_memory();
    remove_shared_memory();
    exit(0);
}

int main() {
    signal(SIGINT, signal_handler);
    create_shared_memory();
    attach_shared_memory();

    while (1) {
        printf("Получено число: %d\n", shared_data_ptr->number);
        sleep(1);
    }

    return 0;
}
