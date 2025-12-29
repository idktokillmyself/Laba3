#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>
#include "DynamicArray.hpp"

template<typename T>
class Stack {
private:
    DynamicArray<T> data;
    
public:
    Stack() = default;
    ~Stack() = default;
    
    // Основной интерфейс
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    
    // Информация
    bool isEmpty() const;
    size_t size() const;
    void clear();
    
    // Сериализация
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);
    void serializeBinary(const std::string& filename) const;
    void deserializeBinary(const std::string& filename);
};

#include "Stack.tpp"

#endif // STACK_HPP
