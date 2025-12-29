template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T& value) {
    auto newNode = std::make_unique<Node>(value);
    
    if (!head) {
        head = std::move(newNode);
        tail = head.get();
    } else {
        newNode->next = std::move(head);
        newNode->next->prev = newNode.get();
        head = std::move(newNode);
    }
    ++size;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T& value) {
    auto newNode = std::make_unique<Node>(value);
    
    if (!tail) {
        head = std::move(newNode);
        tail = head.get();
    } else {
        newNode->prev = tail;
        tail->next = std::move(newNode);
        tail = tail->next.get();
    }
    ++size;
}

template<typename T>
void DoublyLinkedList<T>::pop_front() {
    if (!head) return;
    
    if (head.get() == tail) {
        head.reset();
        tail = nullptr;
    } else {
        head = std::move(head->next);
        head->prev = nullptr;
    }
    --size;
}

template<typename T>
void DoublyLinkedList<T>::pop_back() {
    if (!tail) return;
    
    if (head.get() == tail) {
        head.reset();
        tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next.reset();
    }
    --size;
}

template<typename T>
void DoublyLinkedList<T>::insert(size_t index, const T& value) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        push_front(value);
        return;
    }
    
    if (index == size) {
        push_back(value);
        return;
    }
    
    auto newNode = std::make_unique<Node>(value);
    Node* current = head.get();
    
    for (size_t i = 0; i < index; ++i) {
        current = current->next.get();
    }
    
    newNode->prev = current->prev;
    newNode->next = std::move(current->prev->next);
    current->prev->next = std::move(newNode);
    current->prev = newNode.get();
    
    ++size;
}

template<typename T>
void DoublyLinkedList<T>::remove(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    if (index == 0) {
        pop_front();
        return;
    }
    
    if (index == size - 1) {
        pop_back();
        return;
    }
    
    Node* current = head.get();
    for (size_t i = 0; i < index; ++i) {
        current = current->next.get();
    }
    
    current->prev->next = std::move(current->next);
    if (current->next) {
        current->next->prev = current->prev;
    }
    
    --size;
}

template<typename T>
T& DoublyLinkedList<T>::at(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    Node* current = head.get();
    for (size_t i = 0; i < index; ++i) {
        current = current->next.get();
    }
    
    return current->data;
}

template<typename T>
const T& DoublyLinkedList<T>::at(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    
    const Node* current = head.get();
    for (size_t i = 0; i < index; ++i) {
        current = current->next.get();
    }
    
    return current->data;
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
size_t DoublyLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
void DoublyLinkedList<T>::clear() {
    while (!isEmpty()) {
        pop_front();
    }
}

template<typename T>
int DoublyLinkedList<T>::find(const T& value) const {
    const Node* current = head.get();
    int index = 0;
    
    while (current) {
        if (current->data == value) {
            return index;
        }
        current = current->next.get();
        ++index;
    }
    
    return -1;
}

template<typename T>
void DoublyLinkedList<T>::serialize(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    ofs << size << std::endl;
    const Node* current = head.get();
    while (current) {
        ofs << current->data << std::endl;
        current = current->next.get();
    }
}

template<typename T>
void DoublyLinkedList<T>::deserialize(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    clear();
    size_t newSize;
    ifs >> newSize;
    
    for (size_t i = 0; i < newSize; ++i) {
        T value;
        ifs >> value;
        push_back(value);
    }
}

template<typename T>
void DoublyLinkedList<T>::printForward(std::ostream& os) const {
    const Node* current = head.get();
    os << "[";
    while (current) {
        os << current->data;
        if (current->next) {
            os << " <-> ";
        }
        current = current->next.get();
    }
    os << "]" << std::endl;
}

template<typename T>
void DoublyLinkedList<T>::printBackward(std::ostream& os) const {
    const Node* current = tail;
    os << "[";
    while (current) {
        os << current->data;
        if (current->prev) {
            os << " <-> ";
        }
        current = current->prev;
    }
    os << "]" << std::endl;
}
