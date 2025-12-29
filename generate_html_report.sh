#!/bin/bash

echo "=== ГЕНЕРАЦИЯ HTML ОТЧЕТА О ПОКРЫТИИ ТЕСТАМИ ==="
echo ""

# Проверяем установленные инструменты
if ! command -v gcov &> /dev/null; then
    echo "Ошибка: gcov не установлен!"
    echo "Установите: sudo apt-get install gcc"
    exit 1
fi

if ! command -v lcov &> /dev/null; then
    echo "Ошибка: lcov не установлен!"
    echo "Установите: sudo apt-get install lcov"
    exit 1
fi

if ! command -v genhtml &> /dev/null; then
    echo "Ошибка: genhtml не установлен!"
    echo "Установите: sudo apt-get install lcov"
    exit 1
fi

# Создаем директорию для отчета
mkdir -p coverage_report

echo "1. Компиляция с флагами coverage..."
g++ -std=c++17 -Wall -Wextra -I./include -O0 -g -fprofile-arcs -ftest-coverage \
    -c src/AVLTree.cpp -o src/AVLTree.gcno
g++ -std=c++17 -Wall -Wextra -I./include -O0 -g -fprofile-arcs -ftest-coverage \
    -c src/test_coverage.cpp -o src/test_coverage.gcno

echo "2. Линковка..."
g++ -std=c++17 -Wall -Wextra -I./include -O0 -g -fprofile-arcs -ftest-coverage \
    src/AVLTree.cpp src/test_coverage.cpp -o coverage_test

echo "3. Запуск тестов..."
./coverage_test

echo "4. Генерация данных coverage..."
gcov src/AVLTree.cpp src/test_coverage.cpp

echo "5. Создание HTML отчета..."
lcov --capture --directory . --output-file coverage.info \
    --rc lcov_branch_coverage=1

# Фильтруем системные файлы
lcov --remove coverage.info '/usr/*' '*/tests/*' '*/include/*' --output-file coverage.filtered.info

echo "6. Генерация HTML..."
genhtml coverage.filtered.info --output-directory coverage_report \
    --branch-coverage --title "Лабораторная работа №3: Покрытие тестами"

echo ""
echo "=== ОТЧЕТ СОЗДАН ==="
echo "Файлы:"
echo "  - coverage.info - данные coverage"
echo "  - coverage.filtered.info - отфильтрованные данные"
echo "  - coverage_report/index.html - HTML отчет"
echo ""
echo "Отчет покрытия:"
echo "  Lines: $(grep 'lines.*:' coverage_report/index.html | head -1 | sed 's/.*>//')"
echo "  Functions: $(grep 'functions.*:' coverage_report/index.html | head -1 | sed 's/.*>//')"
echo "  Branches: $(grep 'branches.*:' coverage_report/index.html | head -1 | sed 's/.*>//')"
echo ""

# Открываем отчет в браузере если возможно
if command -v xdg-open &> /dev/null; then
    echo "Открываю отчет в браузере..."
    xdg-open coverage_report/index.html
elif command -v open &> /dev/null; then
    echo "Открываю отчет в браузере..."
    open coverage_report/index.html
else
    echo "Откройте файл coverage_report/index.html в браузере"
fi

# Очистка временных файлов
rm -f coverage_test *.gcda *.gcno *.gcov coverage.info coverage.filtered.info
rm -f test_coverage_avl.txt
