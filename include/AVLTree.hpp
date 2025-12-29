#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

class AVLTree {
private:
    struct Node {
        std::string key;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        int height;
        
        explicit Node(const std::string& k) 
            : key(k), left(nullptr), right(nullptr), height(1) {}
        
        // Запрещаем копирование
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        
        // Разрешаем перемещение
        Node(Node&&) = default;
        Node& operator=(Node&&) = default;
    };
    
    std::unique_ptr<Node> root;
    std::string treeName;
    
    // Вспомогательные методы
    int height(const Node* node) const;
    int balanceFactor(const Node* node) const;
    void updateHeight(Node* node);
    
    // Вращения
    std::unique_ptr<Node> rotateRight(std::unique_ptr<Node> y);
    std::unique_ptr<Node> rotateLeft(std::unique_ptr<Node> x);
    std::unique_ptr<Node> balance(std::unique_ptr<Node> node);
    
    // Рекурсивные операции
    std::unique_ptr<Node> insert(std::unique_ptr<Node> node, const std::string& key);
    std::unique_ptr<Node> remove(std::unique_ptr<Node> node, const std::string& key);
    bool contains(const Node* node, const std::string& key) const;
    Node* findMin(Node* node);  // Возвращаем указатель, а не unique_ptr
    
    // Обходы
    void inorder(const Node* node, std::vector<std::string>& result) const;
    void printTree(const Node* node, int space, std::ostream& os) const;
    void clear(Node* node);
    
public:
    // Конструкторы/деструктор
    AVLTree();
    explicit AVLTree(const std::string& name);
    ~AVLTree();
    
    // Основной интерфейс
    void insert(const std::string& key);
    void remove(const std::string& key);
    bool contains(const std::string& key) const;
    bool isEmpty() const;
    void clear();
    
    // Дополнительные методы
    std::vector<std::string> inorderTraversal() const;
    void print(std::ostream& os = std::cout) const;
    
    // Геттеры/сеттеры
    std::string getName() const;
    void setName(const std::string& name);
    int getHeight() const;
    bool isBalanced() const;
    
    // Сериализация/десериализация
    void serialize(const std::string& filename) const;
    void deserialize(const std::string& filename);
    void serializeBinary(const std::string& filename) const;
    void deserializeBinary(const std::string& filename);
    
private:
    bool isBalanced(const Node* node) const;
    void serializeNode(std::ostream& os, const Node* node) const;
    std::unique_ptr<Node> deserializeNode(std::istream& is);
    void serializeNodeBinary(std::ofstream& ofs, const Node* node) const;
    std::unique_ptr<Node> deserializeNodeBinary(std::ifstream& ifs);
};

#endif // AVLTREE_HPP
