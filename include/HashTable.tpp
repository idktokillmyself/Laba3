template<typename K, typename V>
HashTable<K, V>::HashTable(size_t initialCapacity) 
    : capacity(initialCapacity > 0 ? initialCapacity : 16), size(0) {
    table.resize(capacity);
}

template<typename K, typename V>
size_t HashTable<K, V>::hash(const K& key) const {
    std::hash<K> hasher;
    return hasher(key) % capacity;
}

template<typename K, typename V>
void HashTable<K, V>::rehash(size_t newCapacity) {
    std::vector<std::list<Entry>> newTable(newCapacity);
    
    for (const auto& chain : table) {
        for (const auto& entry : chain) {
            size_t newIndex = std::hash<K>{}(entry.key) % newCapacity;
            newTable[newIndex].push_back(entry);
        }
    }
    
    table = std::move(newTable);
    capacity = newCapacity;
}

template<typename K, typename V>
void HashTable<K, V>::insert(const K& key, const V& value) {
    if (loadFactor() > 0.75) {
        rehash(capacity * 2);
    }
    
    size_t index = hash(key);
    
    // Проверяем, нет ли уже такого ключа
    for (auto& entry : table[index]) {
        if (entry.key == key) {
            entry.value = value;
            return;
        }
    }
    
    // Добавляем новую запись
    table[index].emplace_back(key, value);
    ++size;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& key) {
    size_t index = hash(key);
    
    auto& chain = table[index];
    for (auto it = chain.begin(); it != chain.end(); ++it) {
        if (it->key == key) {
            chain.erase(it);
            --size;
            return true;
        }
    }
    
    return false;
}

template<typename K, typename V>
bool HashTable<K, V>::contains(const K& key) const {
    size_t index = hash(key);
    
    for (const auto& entry : table[index]) {
        if (entry.key == key) {
            return true;
        }
    }
    
    return false;
}

template<typename K, typename V>
V& HashTable<K, V>::get(const K& key) {
    size_t index = hash(key);
    
    for (auto& entry : table[index]) {
        if (entry.key == key) {
            return entry.value;
        }
    }
    
    throw std::runtime_error("Key not found");
}

template<typename K, typename V>
const V& HashTable<K, V>::get(const K& key) const {
    size_t index = hash(key);
    
    for (const auto& entry : table[index]) {
        if (entry.key == key) {
            return entry.value;
        }
    }
    
    throw std::runtime_error("Key not found");
}

template<typename K, typename V>
bool HashTable<K, V>::isEmpty() const {
    return size == 0;
}

template<typename K, typename V>
size_t HashTable<K, V>::getSize() const {
    return size;
}

template<typename K, typename V>
size_t HashTable<K, V>::getCapacity() const {
    return capacity;
}

template<typename K, typename V>
void HashTable<K, V>::clear() {
    for (auto& chain : table) {
        chain.clear();
    }
    size = 0;
}

template<typename K, typename V>
void HashTable<K, V>::serialize(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    ofs << size << " " << capacity << std::endl;
    for (const auto& chain : table) {
        ofs << chain.size() << " ";
        for (const auto& entry : chain) {
            ofs << entry.key << " " << entry.value << " ";
        }
        ofs << std::endl;
    }
}

template<typename K, typename V>
void HashTable<K, V>::deserialize(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    clear();
    size_t newSize, newCapacity;
    ifs >> newSize >> newCapacity;
    
    table.resize(newCapacity);
    capacity = newCapacity;
    
    for (size_t i = 0; i < newCapacity; ++i) {
        size_t chainSize;
        ifs >> chainSize;
        
        for (size_t j = 0; j < chainSize; ++j) {
            K key;
            V value;
            ifs >> key >> value;
            table[i].emplace_back(key, value);
            ++size;
        }
    }
}

template<typename K, typename V>
double HashTable<K, V>::loadFactor() const {
    return static_cast<double>(size) / capacity;
}

template<typename K, typename V>
size_t HashTable<K, V>::maxChainLength() const {
    size_t maxLen = 0;
    for (const auto& chain : table) {
        if (chain.size() > maxLen) {
            maxLen = chain.size();
        }
    }
    return maxLen;
}
