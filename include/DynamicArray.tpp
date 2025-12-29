template<typename T>
DynamicArray<T>::DynamicArray() : capacity(10), size(0) {
    data = std::make_unique<T[]>(capacity);
}

template<typename T>
DynamicArray<T>::DynamicArray(size_t initialCapacity) 
    : capacity(initialCapacity > 0 ? initialCapacity : 10), size(0) {
    data = std::make_unique<T[]>(capacity);
}

template<typename T>
void DynamicArray<T>::resize(size_t newCapacity) {
    auto newData = std::make_unique<T[]>(newCapacity);
    for (size_t i = 0; i < size; ++i) {
        newData[i] = std::move(data[i]);
    }
    data = std::move(newData);
    capacity = newCapacity;
}

template<typename T>
void DynamicArray<T>::push_back(const T& value) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    data[size++] = value;
}

template<typename T>
void DynamicArray<T>::pop_back() {
    if (size > 0) {
        --size;
    }
}

template<typename T>
void DynamicArray<T>::insert(size_t index, const T& value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    
    if (size >= capacity) {
        resize(capacity * 2);
    }
    
    for (size_t i = size; i > index; --i) {
        data[i] = std::move(data[i - 1]);
    }
    
    data[index] = value;
    ++size;
}

template<typename T>
void DynamicArray<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = std::move(data[i + 1]);
    }
    --size;
}

template<typename T>
T& DynamicArray<T>::at(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::at(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
T& DynamicArray<T>::operator[](size_t index) {
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::operator[](size_t index) const {
    return data[index];
}

template<typename T>
bool DynamicArray<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
size_t DynamicArray<T>::getSize() const {
    return size;
}

template<typename T>
size_t DynamicArray<T>::getCapacity() const {
    return capacity;
}

template<typename T>
void DynamicArray<T>::clear() {
    size = 0;
}

template<typename T>
int DynamicArray<T>::find(const T& value) const {
    for (size_t i = 0; i < size; ++i) {
        if (data[i] == value) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template<typename T>
void DynamicArray<T>::serialize(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    ofs << size << std::endl;
    for (size_t i = 0; i < size; ++i) {
        ofs << data[i] << std::endl;
    }
}

template<typename T>
void DynamicArray<T>::deserialize(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    size_t newSize;
    ifs >> newSize;
    
    clear();
    for (size_t i = 0; i < newSize; ++i) {
        T value;
        ifs >> value;
        push_back(value);
    }
}

template<typename T>
void DynamicArray<T>::serializeBinary(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for binary writing: " + filename);
    }
    
    ofs.write(reinterpret_cast<const char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        ofs.write(reinterpret_cast<const char*>(&data[i]), sizeof(T));
    }
}

template<typename T>
void DynamicArray<T>::deserializeBinary(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for binary reading: " + filename);
    }
    
    size_t newSize;
    ifs.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    
    clear();
    for (size_t i = 0; i < newSize; ++i) {
        T value;
        ifs.read(reinterpret_cast<char*>(&value), sizeof(T));
        push_back(value);
    }
}
