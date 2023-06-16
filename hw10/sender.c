#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

__pid_t sender_pid, receiver_pid;

void sendBit(__int8_t bit) {
    if (bit == 0) {
        kill(receiver_pid, SIGUSR1);
    } else {
        kill(receiver_pid, SIGUSR2);
    }
}

void confirmationHandler(int sig) {
}

int main(int argc, char *argv[]) {
    (void)signal(SIGUSR1, confirmationHandler);

    sender_pid = getpid();
    int sending_integer;
    printf("Идентификатор отправителя: %d\n", sender_pid);
    printf("Введите идентификатор получателя: ");
    scanf("%d", &receiver_pid);

    printf("Введите целое число для отправки: ");
    scanf("%d", &sending_integer);

    printf("Отправка числа %d на идентификатор %d\n", sending_integer, receiver_pid);

    if (sending_integer < 0) {
        sendBit(1);
        sending_integer = -sending_integer;
    } else {
        sendBit(0);
    }
    pause();

    while (sending_integer > 0) {
        sendBit(sending_integer & 1);
        sending_integer >>= 1;

        pause();
    }

    kill(receiver_pid, SIGINT);

    printf("Отправка числа завершена.\n");

    return 0;
}
