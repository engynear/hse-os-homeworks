#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include "shared_memory.h"

void signal_handler(int signum) {
    detach_shared_memory();
    remove_shared_memory();
    exit(0);
}

int main() {
    signal(SIGINT, signal_handler);
    create_shared_memory();
    attach_shared_memory();

    srand(getpid());

    while (1) {
        generate_random_number();
        sleep(1);
    }

    return 0;
}