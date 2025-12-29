#ifndef SINGLYLINKEDLIST_HPP
#define SINGLYLINKEDLIST_HPP

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>

template<typename T>
class SinglyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };
    
    std::unique_ptr<Node> head;
    size_t size;
    
public:
    SinglyLinkedList();
    ~SinglyLinkedList() = default;
    
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
    void print(std::ostream& os = std::cout) const;
};

#include "SinglyLinkedList.tpp"

#endif // SINGLYLINKEDLIST_HPP
