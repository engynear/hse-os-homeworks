#!/bin/bash

# Функция, которая приветствует пользователя и выводит текущую дату
function greet_lector() {
    echo "Добрый день, Александр Иванович!"
    echo "Сегодня $(date)"
}

function greet_seminarian() {
    echo "Добрый день, Сергей Александрович!"
    echo "Сегодня $(date)"
}

# Обратный отсчет
function countdown() {
    for ((i=5; i>=1; i--)); do
        echo $i
        sleep 1
    done
}

# Запуск обратного отсчета
countdown

# Запрос информации о пользователе
read -p "Вы лектор по дисциплине 'операционные системы'? (y/n): " is_lector

if [[ $is_lector == "y" ]]; then
    greet_lector
else
    greet_seminarian
fi
