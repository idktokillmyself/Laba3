#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>

template<typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;
        
        explicit Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    
    std::unique_ptr<Node> head;
    Node* tail;
    size_t size;
    
public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    
    // Основной интерфейс
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void insert(size_t index, const T& value);
    void remove(size_t index);
    T& at(size_t index);
    const T& at(size_t index) const;
    
    // Информация
    bool isEmpty() const;
    size_t getSize() const;
    void clear();
    
    // Поиск
    int find(const T& value) const;
    
    // Сериализация
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);
    
    // Вывод
    void printForward(std::ostream& os = std::cout) const;
    void printBackward(std::ostream& os = std::cout) const;
};

#include "DoublyLinkedList.tpp"

#endif // DOUBLYLINKEDLIST_HPP
