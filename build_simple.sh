#!/bin/bash

echo "=== Компиляция проекта ==="

# Компилируем основной файл с AVL деревом
g++ -std=c++17 -I./include -c src/AVLTree.cpp -o AVLTree.o
g++ -std=c++17 -I./include -c src/main.cpp -o main.o

# Линкуем вместе
g++ -std=c++17 AVLTree.o main.o -o main_program

echo "=== Запуск демо ==="
./main_program

# Очистка
rm -f *.o main_program
