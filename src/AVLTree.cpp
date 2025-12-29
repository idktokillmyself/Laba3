#include "AVLTree.hpp"
#include <algorithm>
#include <queue>
#include <sstream>
#include <cstring>

// Конструкторы
AVLTree::AVLTree() : root(nullptr), treeName("UnnamedTree") {}

AVLTree::AVLTree(const std::string& name) : root(nullptr), treeName(name) {}

AVLTree::~AVLTree() {
    clear();
}

// Вспомогательные методы
int AVLTree::height(const Node* node) const {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(const Node* node) const {
    return node ? height(node->left.get()) - height(node->right.get()) : 0;
}

void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left.get()), height(node->right.get()));
    }
}

// Вращения
std::unique_ptr<AVLTree::Node> AVLTree::rotateRight(std::unique_ptr<Node> y) {
    auto x = std::move(y->left);
    y->left = std::move(x->right);
    x->right = std::move(y);
    
    updateHeight(x->right.get());
    updateHeight(x.get());
    
    return x;
}

std::unique_ptr<AVLTree::Node> AVLTree::rotateLeft(std::unique_ptr<Node> x) {
    auto y = std::move(x->right);
    x->right = std::move(y->left);
    y->left = std::move(x);
    
    updateHeight(y->left.get());
    updateHeight(y.get());
    
    return y;
}

std::unique_ptr<AVLTree::Node> AVLTree::balance(std::unique_ptr<Node> node) {
    updateHeight(node.get());
    int bf = balanceFactor(node.get());
    
    if (bf > 1) {
        if (balanceFactor(node->left.get()) < 0) {
            node->left = rotateLeft(std::move(node->left));
        }
        return rotateRight(std::move(node));
    }
    
    if (bf < -1) {
        if (balanceFactor(node->right.get()) > 0) {
            node->right = rotateRight(std::move(node->right));
        }
        return rotateLeft(std::move(node));
    }
    
    return node;
}

// Рекурсивные операции
std::unique_ptr<AVLTree::Node> AVLTree::insert(std::unique_ptr<Node> node, const std::string& key) {
    if (!node) {
        return std::make_unique<Node>(key);
    }
    
    if (key < node->key) {
        node->left = insert(std::move(node->left), key);
    } else if (key > node->key) {
        node->right = insert(std::move(node->right), key);
    } else {
        return node; // Дубликаты не допускаются
    }
    
    return balance(std::move(node));
}

std::unique_ptr<AVLTree::Node> AVLTree::remove(std::unique_ptr<Node> node, const std::string& key) {
    if (!node) return nullptr;
    
    if (key < node->key) {
        node->left = remove(std::move(node->left), key);
    } else if (key > node->key) {
        node->right = remove(std::move(node->right), key);
    } else {
        // Узел найден
        if (!node->left || !node->right) {
            node = std::move(node->left ? node->left : node->right);
        } else {
            Node* minRight = findMin(node->right.get());
            node->key = minRight->key;
            node->right = remove(std::move(node->right), minRight->key);
        }
    }
    
    if (!node) return nullptr;
    return balance(std::move(node));
}

bool AVLTree::contains(const Node* node, const std::string& key) const {
    if (!node) return false;
    if (key == node->key) return true;
    return key < node->key ? contains(node->left.get(), key) : contains(node->right.get(), key);
}

AVLTree::Node* AVLTree::findMin(Node* node) {
    while (node && node->left) {
        node = node->left.get();
    }
    return node;
}

// Обходы
void AVLTree::inorder(const Node* node, std::vector<std::string>& result) const {
    if (node) {
        inorder(node->left.get(), result);
        result.push_back(node->key);
        inorder(node->right.get(), result);
    }
}

void AVLTree::printTree(const Node* node, int space, std::ostream& os) const {
    const int COUNT = 4;
    
    if (!node) return;
    
    space += COUNT;
    printTree(node->right.get(), space, os);
    
    os << std::endl;
    for (int i = COUNT; i < space; i++) {
        os << " ";
    }
    os << node->key << "(" << node->height << ")" << std::endl;
    
    printTree(node->left.get(), space, os);
}

void AVLTree::clear(Node* node) {
    if (node) {
        clear(node->left.get());
        clear(node->right.get());
        node->left.reset();
        node->right.reset();
    }
}

// Публичный интерфейс
void AVLTree::insert(const std::string& key) {
    root = insert(std::move(root), key);
}

void AVLTree::remove(const std::string& key) {
    root = remove(std::move(root), key);
}

bool AVLTree::contains(const std::string& key) const {
    return contains(root.get(), key);
}

bool AVLTree::isEmpty() const {
    return !root;
}

void AVLTree::clear() {
    root.reset();
}

std::vector<std::string> AVLTree::inorderTraversal() const {
    std::vector<std::string> result;
    inorder(root.get(), result);
    return result;
}

void AVLTree::print(std::ostream& os) const {
    os << "Tree: " << treeName << std::endl;
    if (isEmpty()) {
        os << "  [empty]" << std::endl;
    } else {
        printTree(root.get(), 0, os);
        auto traversal = inorderTraversal();
        os << "In-order: ";
        for (size_t i = 0; i < traversal.size(); ++i) {
            os << traversal[i];
            if (i < traversal.size() - 1) os << " ";
        }
        os << std::endl << std::endl;
    }
}

// Геттеры/сеттеры
std::string AVLTree::getName() const {
    return treeName;
}

void AVLTree::setName(const std::string& name) {
    treeName = name;
}

int AVLTree::getHeight() const {
    return height(root.get());
}

bool AVLTree::isBalanced() const {
    return isBalanced(root.get());
}

bool AVLTree::isBalanced(const Node* node) const {
    if (!node) return true;
    
    int bf = balanceFactor(node);
    if (bf < -1 || bf > 1) return false;
    
    return isBalanced(node->left.get()) && isBalanced(node->right.get());
}

// Сериализация/десериализация (текстовый формат)
void AVLTree::serialize(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for writing: " + filename);
    }
    
    ofs << treeName << std::endl;
    serializeNode(ofs, root.get());
}

void AVLTree::serializeNode(std::ostream& os, const Node* node) const {
    if (!node) {
        os << "#" << std::endl;
        return;
    }
    
    os << node->key << " " << node->height << std::endl;
    serializeNode(os, node->left.get());
    serializeNode(os, node->right.get());
}

void AVLTree::deserialize(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for reading: " + filename);
    }
    
    std::getline(ifs, treeName);
    root = deserializeNode(ifs);
}

std::unique_ptr<AVLTree::Node> AVLTree::deserializeNode(std::istream& is) {
    std::string line;
    if (!std::getline(is, line)) {
        return nullptr;
    }
    
    if (line == "#") {
        return nullptr;
    }
    
    std::istringstream iss(line);
    std::string key;
    int height;
    iss >> key >> height;
    
    auto node = std::make_unique<Node>(key);
    node->height = height;
    node->left = deserializeNode(is);
    node->right = deserializeNode(is);
    
    return node;
}

// Бинарная сериализация
void AVLTree::serializeBinary(const std::string& filename) const {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        throw std::runtime_error("Cannot open file for binary writing: " + filename);
    }
    
    // Записываем имя дерева
    size_t nameLen = treeName.length();
    ofs.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    ofs.write(treeName.c_str(), nameLen);
    
    serializeNodeBinary(ofs, root.get());
}

void AVLTree::serializeNodeBinary(std::ofstream& ofs, const Node* node) const {
    char marker = node ? 'N' : '#';
    ofs.write(&marker, 1);
    
    if (!node) return;
    
    // Записываем ключ
    size_t keyLen = node->key.length();
    ofs.write(reinterpret_cast<const char*>(&keyLen), sizeof(keyLen));
    ofs.write(node->key.c_str(), keyLen);
    
    // Записываем высоту
    ofs.write(reinterpret_cast<const char*>(&node->height), sizeof(node->height));
    
    // Рекурсивно записываем потомков
    serializeNodeBinary(ofs, node->left.get());
    serializeNodeBinary(ofs, node->right.get());
}

void AVLTree::deserializeBinary(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        throw std::runtime_error("Cannot open file for binary reading: " + filename);
    }
    
    // Читаем имя дерева
    size_t nameLen;
    ifs.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    treeName.resize(nameLen);
    ifs.read(&treeName[0], nameLen);
    
    root = deserializeNodeBinary(ifs);
}

std::unique_ptr<AVLTree::Node> AVLTree::deserializeNodeBinary(std::ifstream& ifs) {
    char marker;
    ifs.read(&marker, 1);
    
    if (marker == '#') {
        return nullptr;
    }
    
    auto node = std::make_unique<Node>("");
    
    // Читаем ключ
    size_t keyLen;
    ifs.read(reinterpret_cast<char*>(&keyLen), sizeof(keyLen));
    node->key.resize(keyLen);
    ifs.read(&node->key[0], keyLen);
    
    // Читаем высоту
    ifs.read(reinterpret_cast<char*>(&node->height), sizeof(node->height));
    
    // Рекурсивно читаем потомков
    node->left = deserializeNodeBinary(ifs);
    node->right = deserializeNodeBinary(ifs);
    
    return node;
}
