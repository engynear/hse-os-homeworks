#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

__pid_t this_pid, sender_pid;
__int8_t received_bit = -1, is_receiving = 1;

void resiveBitHandler(int sig) {
    if (sig == SIGUSR1) {
        received_bit = 0;
    }
    else if (sig == SIGUSR2) {
        received_bit = 1;
    } else if (sig == SIGINT) {
        is_receiving = 0;
    } else {
        printf("Получен неизвестный сигнал %d\n", sig);
        exit(1);
    }
}

void sendConfirmation() {
    kill(sender_pid, SIGUSR1);
}

int main(int argc, char *argv[]) {
    (void)signal(SIGUSR1, resiveBitHandler);
    (void)signal(SIGUSR2, resiveBitHandler);
    (void)signal(SIGINT, resiveBitHandler);

    this_pid = getpid();
    printf("PID: %d\n", this_pid);
    printf("Введите PID отправителя: ");
    scanf("%d", &sender_pid);

    sendConfirmation();

    printf("Ожидание целого числа от PID %d\n", sender_pid);

    __int8_t resived_bits[32], is_negative, iteration = 0;

    pause();
    is_negative = received_bit;
    usleep(100000);
    sendConfirmation();

    while (is_receiving) {
        pause();
        resived_bits[iteration++] = received_bit;
        sendConfirmation();
    }

    __int32_t resived_integer = 0;
    for (int i = 0; i < iteration - 1; i++) {
        resived_integer |= resived_bits[i] << i;
    }

    if (is_negative) {
        resived_integer = -resived_integer;
    }

    printf("Получено целое число %d от PID %d\n", resived_integer, sender_pid);

    return 0;
}
