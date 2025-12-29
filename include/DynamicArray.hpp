#ifndef DYNAMICARRAY_HPP
#define DYNAMICARRAY_HPP

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <stdexcept>

template<typename T>
class DynamicArray {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t size;
    
    void resize(size_t newCapacity);
    
public:
    DynamicArray();
    explicit DynamicArray(size_t initialCapacity);
    ~DynamicArray() = default;
    
    // Запрет копирования
    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;
    
    // Разрешение перемещения
    DynamicArray(DynamicArray&&) = default;
    DynamicArray& operator=(DynamicArray&&) = default;
    
    // Основной интерфейс
    void push_back(const T& value);
    void pop_back();
    void insert(size_t index, const T& value);
    void remove(size_t index);
    T& at(size_t index);
    const T& at(size_t index) const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    
    // Информация
    bool isEmpty() const;
    size_t getSize() const;
    size_t getCapacity() const;
    void clear();
    
    // Поиск
    int find(const T& value) const;
    
    // Сериализация
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);
    void serializeBinary(const std::string& filename) const;
    void deserializeBinary(const std::string& filename);
    
    // Итераторы (упрощенные)
    T* begin() { return data.get(); }
    const T* begin() const { return data.get(); }
    T* end() { return data.get() + size; }
    const T* end() const { return data.get() + size; }
};

#include "DynamicArray.tpp"

#endif // DYNAMICARRAY_HPP
