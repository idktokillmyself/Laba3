#include <iostream>
#include "AVLTree.hpp"

int main() {
    std::cout << "=== Тест AVL дерева (ООП версия) ===" << std::endl;
    
    // Создаем дерево
    AVLTree tree("MyTree");
    
    // Тест 1: Вставка
    std::cout << "\n1. Тест вставки элементов:" << std::endl;
    std::string elements[] = {"50", "30", "70", "20", "40", "60", "80"};
    for (const auto& elem : elements) {
        std::cout << "Вставляем: " << elem << std::endl;
        tree.insert(elem);
    }
    
    std::cout << "\nДерево после вставок:" << std::endl;
    tree.print();
    
    // Тест 2: Поиск
    std::cout << "\n2. Тест поиска:" << std::endl;
    std::cout << "Содержит '40'? " << (tree.contains("40") ? "Да" : "Нет") << std::endl;
    std::cout << "Содержит '90'? " << (tree.contains("90") ? "Да" : "Нет") << std::endl;
    std::cout << "Содержит '20'? " << (tree.contains("20") ? "Да" : "Нет") << std::endl;
    
    // Тест 3: Удаление
    std::cout << "\n3. Тест удаления:" << std::endl;
    std::cout << "Удаляем '40'" << std::endl;
    tree.remove("40");
    std::cout << "Содержит '40' после удаления? " << (tree.contains("40") ? "Да" : "Нет") << std::endl;
    
    std::cout << "\nДерево после удаления:" << std::endl;
    tree.print();
    
    // Тест 4: Статистика
    std::cout << "\n4. Статистика дерева:" << std::endl;
    std::cout << "Имя: " << tree.getName() << std::endl;
    std::cout << "Высота: " << tree.getHeight() << std::endl;
    std::cout << "Сбалансировано: " << (tree.isBalanced() ? "Да" : "Нет") << std::endl;
    std::cout << "Пустое: " << (tree.isEmpty() ? "Да" : "Нет") << std::endl;
    
    // Тест 5: Обход
    std::cout << "\n5. In-order обход:" << std::endl;
    auto traversal = tree.inorderTraversal();
    std::cout << "Элементы в порядке возрастания: ";
    for (size_t i = 0; i < traversal.size(); ++i) {
        std::cout << traversal[i];
        if (i < traversal.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    
    // Тест 6: Сериализация
    std::cout << "\n6. Тест сериализации:" << std::endl;
    std::cout << "Сохраняем дерево в файл..." << std::endl;
    tree.serialize("tree_data.txt");
    tree.serializeBinary("tree_data.bin");
    std::cout << "Дерево сохранено в tree_data.txt и tree_data.bin" << std::endl;
    
    // Тест 7: Десериализация
    std::cout << "\n7. Тест десериализации:" << std::endl;
    AVLTree loadedTree;
    loadedTree.deserialize("tree_data.txt");
    std::cout << "Загруженное дерево:" << std::endl;
    loadedTree.print();
    
    std::cout << "\n=== Все тесты пройдены! ===" << std::endl;
    
    return 0;
}
