#!/bin/bash

# Создаем директорию сборки
mkdir -p build
cd build

# Конфигурируем CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Собираем проект
make -j$(nproc)

# Запускаем демо
echo "=== Запуск демонстрационной программы ==="
./main

# Запускаем тесты (если есть Google Test)
if [ -f "./tests" ]; then
    echo -e "\n=== Запуск тестов ==="
    ./tests
fi

cd ..
