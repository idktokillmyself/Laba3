#include <iostream>
#include <iomanip>
#include <chrono>
#include "AVLTree.hpp"
#include "DynamicArray.hpp"
#include "SinglyLinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "HashTable.hpp"

using namespace std::chrono;

void printSeparator(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

void demoAVLTree() {
    printSeparator("AVL TREE DEMO");
    
    AVLTree tree("MyTree");
    
    std::cout << "Вставляем элементы: 50, 30, 70, 20, 40, 60, 80, 10, 90" << std::endl;
    tree.insert("50");
    tree.insert("30");
    tree.insert("70");
    tree.insert("20");
    tree.insert("40");
    tree.insert("60");
    tree.insert("80");
    tree.insert("10");
    tree.insert("90");
    
    std::cout << "\nДерево:" << std::endl;
    tree.print();
    
    std::cout << "\nПроверки:" << std::endl;
    std::cout << "Содержит '40'? " << std::boolalpha << tree.contains("40") << std::endl;
    std::cout << "Содержит '95'? " << std::boolalpha << tree.contains("95") << std::endl;
    
    std::cout << "\nУдаляем '40':" << std::endl;
    tree.remove("40");
    std::cout << "Содержит '40' после удаления? " << std::boolalpha << tree.contains("40") << std::endl;
    
    std::cout << "\nСтатистика:" << std::endl;
    std::cout << "Высота: " << tree.getHeight() << std::endl;
    std::cout << "Сбалансировано: " << std::boolalpha << tree.isBalanced() << std::endl;
    
    auto traversal = tree.inorderTraversal();
    std::cout << "In-order обход: ";
    for (const auto& val : traversal) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    tree.serialize("avl_tree.txt");
    tree.serializeBinary("avl_tree.bin");
    std::cout << "\nСохранено в avl_tree.txt и avl_tree.bin" << std::endl;
}

void demoDynamicArray() {
    printSeparator("DYNAMIC ARRAY DEMO");
    
    DynamicArray<int> arr;
    
    std::cout << "Добавляем элементы: 10, 20, 30, 40, 50" << std::endl;
    for (int i = 1; i <= 5; ++i) {
        arr.push_back(i * 10);
    }
    
    std::cout << "Массив: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Размер: " << arr.getSize() << std::endl;
    std::cout << "Емкость: " << arr.getCapacity() << std::endl;
    
    std::cout << "\nВставляем 25 на позицию 2:" << std::endl;
    arr.insert(2, 25);
    
    std::cout << "Массив после вставки: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    std::cout << "\nУдаляем элемент на позиции 1:" << std::endl;
    arr.remove(1);
    
    std::cout << "Массив после удаления: ";
    for (size_t i = 0; i < arr.getSize(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    
    arr.serialize("array.txt");
    arr.serializeBinary("array.bin");
    std::cout << "\nСохранено в array.txt и array.bin" << std::endl;
}

void demoSinglyLinkedList() {
    printSeparator("SINGLY LINKED LIST DEMO");
    
    SinglyLinkedList<std::string> list;
    
    std::cout << "Добавляем элементы: Apple, Banana, Cherry" << std::endl;
    list.push_back("Apple");
    list.push_back("Banana");
    list.push_front("Cherry");
    
    std::cout << "Список: ";
    list.print();
    
    std::cout << "Размер: " << list.getSize() << std::endl;
    std::cout << "Пустой? " << std::boolalpha << list.isEmpty() << std::endl;
    
    std::cout << "\nВставляем 'Date' на позицию 2:" << std::endl;
    list.insert(2, "Date");
    std::cout << "Список: ";
    list.print();
    
    std::cout << "\nУдаляем элемент на позиции 1:" << std::endl;
    list.remove(1);
    std::cout << "Список: ";
    list.print();
    
    std::cout << "\nПоиск 'Date': " << list.find("Date") << std::endl;
    std::cout << "Поиск 'Grape': " << list.find("Grape") << std::endl;
    
    list.serialize("singly_list.txt");
    std::cout << "\nСохранено в singly_list.txt" << std::endl;
}

void demoStack() {
    printSeparator("STACK DEMO");
    
    Stack<std::string> stack;
    
    std::cout << "Добавляем элементы: First, Second, Third" << std::endl;
    stack.push("First");
    stack.push("Second");
    stack.push("Third");
    
    std::cout << "Размер стека: " << stack.size() << std::endl;
    std::cout << "Верхний элемент: " << stack.top() << std::endl;
    
    std::cout << "\nИзвлекаем элемент:" << std::endl;
    stack.pop();
    std::cout << "Верхний элемент после pop: " << stack.top() << std::endl;
    std::cout << "Размер стека: " << stack.size() << std::endl;
    
    std::cout << "\nЕще раз извлекаем:" << std::endl;
    stack.pop();
    std::cout << "Верхний элемент: " << stack.top() << std::endl;
    
    std::cout << "\nПроверка пустоты:" << std::endl;
    std::cout << "Стек пустой? " << std::boolalpha << stack.isEmpty() << std::endl;
    
    stack.serialize("stack.txt");
    stack.serializeBinary("stack.bin");
    std::cout << "\nСохранено в stack.txt и stack.bin" << std::endl;
}

void demoQueue() {
    printSeparator("QUEUE DEMO");
    
    Queue<int> queue;
    
    std::cout << "Добавляем элементы: 10, 20, 30, 40" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    
    std::cout << "Размер очереди: " << queue.size() << std::endl;
    std::cout << "Первый элемент: " << queue.front() << std::endl;
    std::cout << "Последний элемент: " << queue.back() << std::endl;
    
    std::cout << "\nИзвлекаем элемент:" << std::endl;
    queue.dequeue();
    std::cout << "Первый элемент после dequeue: " << queue.front() << std::endl;
    std::cout << "Размер очереди: " << queue.size() << std::endl;
    
    std::cout << "\nЕще раз извлекаем:" << std::endl;
    queue.dequeue();
    std::cout << "Первый элемент: " << queue.front() << std::endl;
    std::cout << "Последний элемент: " << queue.back() << std::endl;
    
    queue.serialize("queue.txt");
    std::cout << "\nСохранено в queue.txt" << std::endl;
}

void demoHashTable() {
    printSeparator("HASH TABLE DEMO");
    
    HashTable<std::string, int> hashTable;
    
    std::cout << "Добавляем элементы:" << std::endl;
    hashTable.insert("apple", 5);
    hashTable.insert("banana", 8);
    hashTable.insert("cherry", 3);
    hashTable.insert("date", 12);
    hashTable.insert("elderberry", 7);
    
    std::cout << "Размер: " << hashTable.getSize() << std::endl;
    std::cout << "Емкость: " << hashTable.getCapacity() << std::endl;
    std::cout << "Коэффициент загрузки: " << hashTable.loadFactor() << std::endl;
    std::cout << "Макс. длина цепочки: " << hashTable.maxChainLength() << std::endl;
    
    std::cout << "\nПолучение значений:" << std::endl;
    std::cout << "apple: " << hashTable.get("apple") << std::endl;
    std::cout << "banana: " << hashTable.get("banana") << std::endl;
    
    std::cout << "\nПроверка наличия:" << std::endl;
    std::cout << "Содержит 'cherry'? " << std::boolalpha << hashTable.contains("cherry") << std::endl;
    std::cout << "Содержит 'fig'? " << std::boolalpha << hashTable.contains("fig") << std::endl;
    
    std::cout << "\nУдаляем 'cherry':" << std::endl;
    hashTable.remove("cherry");
    std::cout << "Содержит 'cherry' после удаления? " << std::boolalpha << hashTable.contains("cherry") << std::endl;
    
    hashTable.serialize("hashtable.txt");
    std::cout << "\nСохранено в hashtable.txt" << std::endl;
}

void benchmarkTest() {
    printSeparator("BENCHMARK TEST");
    
    std::cout << "Тест производительности DynamicArray:" << std::endl;
    DynamicArray<int> benchmarkArray;
    
    auto start = high_resolution_clock::now();
    
    for (int i = 0; i < 10000; ++i) {
        benchmarkArray.push_back(i);
    }
    
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    
    std::cout << "Время добавления 10000 элементов: " << duration.count() << " ms" << std::endl;
    std::cout << "Финальный размер: " << benchmarkArray.getSize() << std::endl;
    std::cout << "Финальная емкость: " << benchmarkArray.getCapacity() << std::endl;
}

int main() {
    std::cout << "=== ЛАБОРАТОРНАЯ РАБОТА №3: ОБЪЕКТНО-ОРИЕНТИРОВАННОЕ ПРОГРАММИРОВАНИЕ ===" << std::endl;
    std::cout << "Демонстрация всех структур данных" << std::endl;
    std::cout << "Структуры: AVL Tree, Dynamic Array, Singly Linked List, Stack, Queue, Hash Table" << std::endl;
    
    demoAVLTree();
    demoDynamicArray();
    demoSinglyLinkedList();
    demoStack();
    demoQueue();
    demoHashTable();
    benchmarkTest();
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  ВСЕ ДЕМО ЗАВЕРШЕНЫ УСПЕШНО!" << std::endl;
    std::cout << "  Созданные файлы:" << std::endl;
    std::cout << "  - avl_tree.txt, avl_tree.bin" << std::endl;
    std::cout << "  - array.txt, array.bin" << std::endl;
    std::cout << "  - singly_list.txt" << std::endl;
    std::cout << "  - stack.txt, stack.bin" << std::endl;
    std::cout << "  - queue.txt" << std::endl;
    std::cout << "  - hashtable.txt" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    return 0;
}
