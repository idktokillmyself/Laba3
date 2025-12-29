#include <iostream>
#include <cassert>
#include "AVLTree.hpp"
#include "DynamicArray.hpp"
#include "SinglyLinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "HashTable.hpp"

void testAVLTree() {
    std::cout << "Testing AVLTree..." << std::endl;
    AVLTree tree;
    
    // Вставка
    tree.insert("50");
    tree.insert("30");
    tree.insert("70");
    tree.insert("20");
    tree.insert("40");
    tree.insert("60");
    tree.insert("80");
    
    assert(tree.contains("50"));
    assert(tree.contains("30"));
    assert(tree.contains("70"));
    assert(!tree.contains("100"));
    
    // Удаление
    tree.remove("40");
    assert(!tree.contains("40"));
    
    // Сериализация
    tree.serialize("test_coverage_avl.txt");
    
    // Десериализация
    AVLTree tree2;
    tree2.deserialize("test_coverage_avl.txt");
    assert(tree2.contains("50"));
    
    std::cout << "AVLTree tests passed!" << std::endl;
}

void testDynamicArray() {
    std::cout << "Testing DynamicArray..." << std::endl;
    DynamicArray<int> arr;
    
    // Push back
    for (int i = 0; i < 10; ++i) {
        arr.push_back(i);
    }
    assert(arr.getSize() == 10);
    assert(arr[5] == 5);
    
    // Insert
    arr.insert(5, 99);
    assert(arr[5] == 99);
    
    // Remove
    arr.remove(5);
    assert(arr[5] == 5);
    
    std::cout << "DynamicArray tests passed!" << std::endl;
}

void testSinglyLinkedList() {
    std::cout << "Testing SinglyLinkedList..." << std::endl;
    SinglyLinkedList<int> list;
    
    // Push back/front
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    
    assert(list.at(0) == 0);
    assert(list.at(1) == 1);
    assert(list.at(2) == 2);
    
    // Insert
    list.insert(2, 99);
    assert(list.at(2) == 99);
    
    // Remove
    list.remove(2);
    assert(list.at(2) == 2);
    
    std::cout << "SinglyLinkedList tests passed!" << std::endl;
}

void testStack() {
    std::cout << "Testing Stack..." << std::endl;
    Stack<int> stack;
    
    assert(stack.isEmpty());
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    assert(!stack.isEmpty());
    assert(stack.top() == 3);
    
    stack.pop();
    assert(stack.top() == 2);
    
    std::cout << "Stack tests passed!" << std::endl;
}

void testQueue() {
    std::cout << "Testing Queue..." << std::endl;
    Queue<int> queue;
    
    assert(queue.isEmpty());
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    assert(!queue.isEmpty());
    assert(queue.front() == 1);
    assert(queue.back() == 3);
    
    queue.dequeue();
    assert(queue.front() == 2);
    
    std::cout << "Queue tests passed!" << std::endl;
}

void testHashTable() {
    std::cout << "Testing HashTable..." << std::endl;
    HashTable<std::string, int> ht;
    
    assert(ht.isEmpty());
    
    ht.insert("one", 1);
    ht.insert("two", 2);
    ht.insert("three", 3);
    
    assert(!ht.isEmpty());
    assert(ht.get("one") == 1);
    assert(ht.get("two") == 2);
    
    ht.remove("two");
    assert(!ht.contains("two"));
    
    std::cout << "HashTable tests passed!" << std::endl;
}

int main() {
    std::cout << "=== RUNNING COVERAGE TESTS ===" << std::endl;
    
    testAVLTree();
    testDynamicArray();
    testSinglyLinkedList();
    testStack();
    testQueue();
    testHashTable();
    
    std::cout << "\n=== ALL TESTS PASSED ===" << std::endl;
    std::cout << "Coverage data generated for HTML report" << std::endl;
    
    // Cleanup
    std::remove("test_coverage_avl.txt");
    
    return 0;
}
