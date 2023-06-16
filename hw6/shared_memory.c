#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include "shared_memory.h"

int shm_id;
struct shared_data *shared_data_ptr;

void create_shared_memory() {
    key_t key = ftok(".", 'R');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    shm_id = shmget(key, sizeof(struct shared_data), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }
}

void attach_shared_memory() {
    shared_data_ptr = (struct shared_data *)shmat(shm_id, NULL, 0);
    if (shared_data_ptr == (struct shared_data *)-1) {
        perror("shmat");
        exit(1);
    }
}

void detach_shared_memory() {
    if (shmdt((void *)shared_data_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
}

void remove_shared_memory() {
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
}

void generate_random_number() {
    shared_data_ptr->number = rand();
}
