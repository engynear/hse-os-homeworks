# ДЗ №4 ОС
Исполнитель: Миронов Павел Андреевич. Группа: БПИ-212

## Условие

1. Разработать программу использующую для работы с текстовыми файлами системные вызовы. Программа на языке C должна прочитать, используя буфер, размер которого превышает читаемые файлы и записать прочитанный файл в файл с другим именем. Имена файлов для чтения и записи задавать с использованием
аргументов командной строки.

## Решение

Программа принимает имена исходного и целевого файлов в качестве аргументов командной строки и осуществляет копирование содержимого исходного файла в целевой файл с помощью буфера, размер которого превышает размер читаемых файлов.

После запуска программы и успешного выполнения копирования файла, программа выведет сообщение "Файл успешно скопирован.". В случае возникновения ошибки при открытии файлов или копирования, будут выведены соответствующие сообщения об ошибке.

## Пример работы программы

```
$ make
$ ./main.o input.txt output.txt
Файл успешно скопирован.
```