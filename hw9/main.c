#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>

const int BUFFER_SIZE = 10000;
key_t sem_key = 777;

int getRandomInt(int begin, int end) {
    return rand() % (end - begin) + begin;
}

int createSem() {
    int semid;

    if ((semid = semget(sem_key++, 2, 0666 | IPC_CREAT)) < 0) {
        printf("Невозможно создать набор семафоров\n");
        exit(-1);
    }

    printf("Набор семафоров создан с идентификатором: %d\n", semid);

    return semid;
}

void deleteSem(int semid) {
    if (semctl(semid, 0, IPC_RMID) < 0) {
        printf("Невозможно удалить набор семафоров\n");
        exit(-1);
    }
}

struct sembuf setSemOperation(int sem_num, int sem_op, int sem_flg) {
    struct sembuf semaphore_operation;
    semaphore_operation.sem_num = sem_num;
    semaphore_operation.sem_op = sem_op;
    semaphore_operation.sem_flg = sem_flg;
    return semaphore_operation;
}

int main(int argc, char const *argv[]) {
    int writer_sem_id, reader_sem_id, writer_process, io_pipe[2], amount_of_operations;
    char buffer_string[BUFFER_SIZE];
    struct sembuf semaphore_operation;

    if (argc == 1) {
        amount_of_operations = 10;
    } else {
        amount_of_operations = atoi(argv[1]);
    }

    writer_sem_id = createSem();
    reader_sem_id = createSem();

    if (pipe(io_pipe) < 0) {
        printf("Невозможно создать канал \n");
        exit(-1);
    }

    int shm_id;
    if ((shm_id = shm_open("/posix-shared-object", O_CREAT | O_RDWR, 0666)) == -1) {
        perror("shm_open");
        exit(1);
    }

    if (ftruncate(shm_id, sizeof(buffer_string)) == -1) {
        perror("ftruncate");
        exit(1);
    }

    char* shared_buffer = mmap(NULL, sizeof(buffer_string), PROT_READ | PROT_WRITE, MAP_SHARED, shm_id, 0);
    if (shared_buffer == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    writer_process = fork();

    if (writer_process < 0) {
        printf("Невозможно создать дочерний процесс \n");
        exit(-1);
    } else if (writer_process == 0) {
        sleep(1);
        for (int i = 0; i < amount_of_operations; i++) {
            int random_number = getRandomInt(0, 100);
            sprintf(buffer_string, "%d", random_number);
            strncpy(shared_buffer, buffer_string, BUFFER_SIZE);

            semaphore_operation = setSemOperation(0, 1, 0);
            if (semop(reader_sem_id, &semaphore_operation, 1) < 0) {
                printf("Невозможно ожидать условия\n");
                exit(-1);
            }

            semaphore_operation = setSemOperation(0, -1, 0);
            if (semop(writer_sem_id, &semaphore_operation, 1) < 0) {
                printf("Невозможно ожидать условия\n");
                exit(-1);
            }
        }

        printf("Писатель завершил работу \n");
    } else {
        for (int i = 0; i < amount_of_operations; i++) {
            semaphore_operation = setSemOperation(0, -1, 0);
            if (semop(reader_sem_id, &semaphore_operation, 1) < 0) {
                printf("Невозможно ожидать условия\n");
                exit(-1);
            }

            strncpy(buffer_string, shared_buffer, BUFFER_SIZE);
            printf("Получено число: %s\n", buffer_string);

            semaphore_operation = setSemOperation(0, 1, 0);
            if (semop(writer_sem_id, &semaphore_operation, 1) < 0) {
                printf("Невозможно ожидать условия\n");
                exit(-1);
            }
        }

        deleteSem(writer_sem_id);
        deleteSem(reader_sem_id);
        printf("Набор семафоров удален \n");

        printf("Читатель завершил работу \n");
    }

    if (munmap(shared_buffer, sizeof(buffer_string)) == -1) {
        perror("munmap");
        exit(1);
    }

    if (shm_unlink("/posix-shared-object") == -1) {
        perror("shm_unlink");
        exit(1);
    }

    return 0;
}