#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>
#include "SinglyLinkedList.hpp"

template<typename T>
class Queue {
private:
    SinglyLinkedList<T> data;
    
public:
    Queue() = default;
    ~Queue() = default;
    
    // Основной интерфейс
    void enqueue(const T& value);
    void dequeue();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    // Информация
    bool isEmpty() const;
    size_t size() const;
    void clear();
    
    // Сериализация
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);
};

#include "Queue.tpp"

#endif // QUEUE_HPP
