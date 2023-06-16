#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int fibonacci(int n)
{
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int factorial(int n)
{
    if (n <= 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Использование: %s <число>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Ошибка при создании процесса.\n");
        return 1;
    }
    else if (pid == 0)
    {
        int fact = factorial(number);
        printf("Факториал числа %d равен %d\n", number, fact);
    }
    else
    {
        int fib = fibonacci(number);
        printf("Число Фибоначчи на позиции %d равно %d\n", number, fib);
        wait(NULL);
    }

    return 0;
}
