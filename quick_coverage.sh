#!/bin/bash

echo "=== БЫСТРАЯ ГЕНЕРАЦИЯ HTML ОТЧЕТА ==="

# Создаем простой тестовый файл
cat > simple_test.cpp << 'TESTEND'
#include "AVLTree.hpp"
#include "DynamicArray.hpp"
#include <cassert>

int main() {
    // Тест AVLTree
    AVLTree avl;
    avl.insert("test");
    assert(avl.contains("test"));
    avl.remove("test");
    assert(!avl.contains("test"));
    
    // Тест DynamicArray
    DynamicArray<int> arr;
    for(int i = 0; i < 100; i++) arr.push_back(i);
    assert(arr.getSize() == 100);
    assert(arr[50] == 50);
    
    return 0;
}
TESTEND

# Компилируем с coverage
g++ -std=c++17 -I./include -fprofile-arcs -ftest-coverage \
    src/AVLTree.cpp simple_test.cpp -o coverage_test

# Запускаем
./coverage_test

# Генерируем отчет
gcov src/AVLTree.cpp
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory html_coverage

echo ""
echo "HTML отчет создан в папке html_coverage"
echo "Покрытие кода:"
echo "---------------"
cat src/AVLTree.cpp.gcov | grep -E "^[[:space:]]*[0-9]+:|^[[:space:]]*#####" | head -20

# Очистка
rm -f simple_test.cpp coverage_test *.gcda *.gcno *.gcov coverage.info
