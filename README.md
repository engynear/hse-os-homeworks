# Домашние работы, дисциплина "Операционные системы", 2 курс ПИ НИУ ВШЭ
Исполнитель: Миронов Павел Андреевич. Группа: БПИ-212

# Сборка и запуск

Для удобства проверки написан docker-compose файл, который поднимает контейнер с gcc (внутри unix).

В папке каждого отдельного задания есть Makefile для сборки проекта.

Пример сборки и запуска 3 задания:

```bash
$ docker-compose up -d
$ docker-compose exec -it gcc bash
$ cd hw3
$ make
$ ./main.o 5
Число Фибоначчи на позиции 5 равно 5
Факториал числа 5 равен 120
```