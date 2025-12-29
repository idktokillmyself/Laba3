#include <iostream>
#include "SinglyLinkedList.hpp"

void testSinglyLinkedList() {
    std::cout << "=== ТЕСТ ОДНОСВЯЗНОГО СПИСКА ===" << std::endl;
    
    SinglyLinkedList<std::string> list;
    
    std::cout << "1. Добавляем элементы: Apple, Banana, Cherry" << std::endl;
    list.push_back("Apple");
    list.push_back("Banana");
    list.push_front("Cherry");
    
    std::cout << "Список: ";
    list.print();
    std::cout << "Размер: " << list.getSize() << std::endl;
    
    std::cout << "\n2. Вставляем 'Date' на позицию 2" << std::endl;
    try {
        list.insert(2, "Date");
        std::cout << "Список: ";
        list.print();
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    std::cout << "\n3. Удаляем элемент на позиции 1" << std::endl;
    try {
        list.remove(1);
        std::cout << "Список: ";
        list.print();
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    std::cout << "\n4. Получаем элемент на позиции 1: ";
    try {
        std::cout << list.at(1) << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }
    
    std::cout << "\n5. Поиск элементов:" << std::endl;
    std::cout << "Поиск 'Date': " << list.find("Date") << std::endl;
    std::cout << "Поиск 'Grape': " << list.find("Grape") << std::endl;
    
    std::cout << "\n=== ТЕСТ ЗАВЕРШЕН ===" << std::endl;
}

int main() {
    testSinglyLinkedList();
    return 0;
}
