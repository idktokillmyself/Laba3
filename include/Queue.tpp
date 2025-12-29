template<typename T>
void Queue<T>::enqueue(const T& value) {
    data.push_back(value);
}

template<typename T>
void Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    data.pop_front();
}

template<typename T>
T& Queue<T>::front() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data.at(0);
}

template<typename T>
const T& Queue<T>::front() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data.at(0);
}

template<typename T>
T& Queue<T>::back() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data.at(data.getSize() - 1);
}

template<typename T>
const T& Queue<T>::back() const {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }
    return data.at(data.getSize() - 1);
}

template<typename T>
bool Queue<T>::isEmpty() const {
    return data.isEmpty();
}

template<typename T>
size_t Queue<T>::size() const {
    return data.getSize();
}

template<typename T>
void Queue<T>::clear() {
    data.clear();
}

template<typename T>
void Queue<T>::serialize(const std::string& filename) const {
    data.serialize(filename);
}

template<typename T>
void Queue<T>::deserialize(const std::string& filename) {
    data.deserialize(filename);
}
