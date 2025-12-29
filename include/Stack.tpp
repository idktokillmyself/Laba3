template<typename T>
void Stack<T>::push(const T& value) {
    data.push_back(value);
}

template<typename T>
void Stack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    data.pop_back();
}

template<typename T>
T& Stack<T>::top() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return data[data.getSize() - 1];
}

template<typename T>
const T& Stack<T>::top() const {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    return data[data.getSize() - 1];
}

template<typename T>
bool Stack<T>::isEmpty() const {
    return data.isEmpty();
}

template<typename T>
size_t Stack<T>::size() const {
    return data.getSize();
}

template<typename T>
void Stack<T>::clear() {
    data.clear();
}

template<typename T>
void Stack<T>::serialize(const std::string& filename) const {
    data.serialize(filename);
}

template<typename T>
void Stack<T>::deserialize(const std::string& filename) {
    data.deserialize(filename);
}

template<typename T>
void Stack<T>::serializeBinary(const std::string& filename) const {
    data.serializeBinary(filename);
}

template<typename T>
void Stack<T>::deserializeBinary(const std::string& filename) {
    data.deserializeBinary(filename);
}
