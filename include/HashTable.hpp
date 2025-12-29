#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <fstream>
#include <stdexcept>

template<typename K, typename V>
class HashTable {
private:
    struct Entry {
        K key;
        V value;
        
        Entry(const K& k, const V& v) : key(k), value(v) {}
    };
    
    std::vector<std::list<Entry>> table;
    size_t capacity;
    size_t size;
    
    size_t hash(const K& key) const;
    void rehash(size_t newCapacity);
    
public:
    explicit HashTable(size_t initialCapacity = 16);
    ~HashTable() = default;
    
    // Основной интерфейс
    void insert(const K& key, const V& value);
    bool remove(const K& key);
    bool contains(const K& key) const;
    V& get(const K& key);
    const V& get(const K& key) const;
    
    // Информация
    bool isEmpty() const;
    size_t getSize() const;
    size_t getCapacity() const;
    void clear();
    
    // Сериализация
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);
    
    // Статистика
    double loadFactor() const;
    size_t maxChainLength() const;
};

#include "HashTable.tpp"

#endif // HASHTABLE_HPP
