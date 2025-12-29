#include <gtest/gtest.h>
#include <fstream>
#include "AVLTree.hpp"
#include "DynamicArray.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "HashTable.hpp"

// ==================== AVL TREE TESTS ====================
TEST(AVLTreeTest, BasicOperations) {
    AVLTree tree;
    
    EXPECT_TRUE(tree.isEmpty());
    EXPECT_EQ(tree.getHeight(), 0);
    
    tree.insert("50");
    tree.insert("30");
    tree.insert("70");
    
    EXPECT_FALSE(tree.isEmpty());
    EXPECT_TRUE(tree.contains("50"));
    EXPECT_TRUE(tree.contains("30"));
    EXPECT_TRUE(tree.contains("70"));
    EXPECT_FALSE(tree.contains("100"));
    
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, Remove) {
    AVLTree tree;
    
    tree.insert("50");
    tree.insert("30");
    tree.insert("70");
    tree.insert("20");
    tree.insert("40");
    
    EXPECT_TRUE(tree.contains("30"));
    tree.remove("30");
    EXPECT_FALSE(tree.contains("30"));
    EXPECT_TRUE(tree.contains("20"));
    EXPECT_TRUE(tree.contains("40"));
    EXPECT_TRUE(tree.isBalanced());
}

TEST(AVLTreeTest, Serialization) {
    AVLTree tree("TestTree");
    tree.insert("A");
    tree.insert("B");
    tree.insert("C");
    
    tree.serialize("test_avl.txt");
    
    AVLTree loaded;
    loaded.deserialize("test_avl.txt");
    
    EXPECT_EQ(loaded.getName(), "TestTree");
    EXPECT_TRUE(loaded.contains("A"));
    EXPECT_TRUE(loaded.contains("B"));
    EXPECT_TRUE(loaded.contains("C"));
    EXPECT_TRUE(loaded.isBalanced());
}

// ==================== DYNAMIC ARRAY TESTS ====================
TEST(DynamicArrayTest, BasicOperations) {
    DynamicArray<int> arr;
    
    EXPECT_TRUE(arr.isEmpty());
    EXPECT_EQ(arr.getSize(), 0);
    
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);
    
    EXPECT_FALSE(arr.isEmpty());
    EXPECT_EQ(arr.getSize(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(DynamicArrayTest, InsertRemove) {
    DynamicArray<std::string> arr;
    
    arr.push_back("A");
    arr.push_back("C");
    
    arr.insert(1, "B");
    EXPECT_EQ(arr[0], "A");
    EXPECT_EQ(arr[1], "B");
    EXPECT_EQ(arr[2], "C");
    
    arr.remove(1);
    EXPECT_EQ(arr[0], "A");
    EXPECT_EQ(arr[1], "C");
}

TEST(DynamicArrayTest, Serialization) {
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    arr.serialize("test_array.txt");
    
    DynamicArray<int> loaded;
    loaded.deserialize("test_array.txt");
    
    EXPECT_EQ(loaded.getSize(), 3);
    EXPECT_EQ(loaded[0], 1);
    EXPECT_EQ(loaded[1], 2);
    EXPECT_EQ(loaded[2], 3);
}

// ==================== SINGLY LINKED LIST TESTS ====================
TEST(SinglyLinkedListTest, BasicOperations) {
    SinglyLinkedList<int> list;
    
    EXPECT_TRUE(list.isEmpty());
    
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(list.getSize(), 3);
    EXPECT_EQ(list.at(0), 0);
    EXPECT_EQ(list.at(1), 1);
    EXPECT_EQ(list.at(2), 2);
}

TEST(SinglyLinkedListTest, Find) {
    SinglyLinkedList<std::string> list;
    
    list.push_back("Apple");
    list.push_back("Banana");
    list.push_back("Cherry");
    
    EXPECT_EQ(list.find("Banana"), 1);
    EXPECT_EQ(list.find("Date"), -1);
}

// ==================== STACK TESTS ====================
TEST(StackTest, BasicOperations) {
    Stack<int> stack;
    
    EXPECT_TRUE(stack.isEmpty());
    
    stack.push(10);
    stack.push(20);
    
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.size(), 2);
    EXPECT_EQ(stack.top(), 20);
    
    stack.pop();
    EXPECT_EQ(stack.top(), 10);
    EXPECT_EQ(stack.size(), 1);
}

// ==================== QUEUE TESTS ====================
TEST(QueueTest, BasicOperations) {
    Queue<std::string> queue;
    
    EXPECT_TRUE(queue.isEmpty());
    
    queue.enqueue("First");
    queue.enqueue("Second");
    
    EXPECT_FALSE(queue.isEmpty());
    EXPECT_EQ(queue.size(), 2);
    EXPECT_EQ(queue.front(), "First");
    EXPECT_EQ(queue.back(), "Second");
    
    queue.dequeue();
    EXPECT_EQ(queue.front(), "Second");
    EXPECT_EQ(queue.size(), 1);
}

// ==================== HASH TABLE TESTS ====================
TEST(HashTableTest, BasicOperations) {
    HashTable<std::string, int> ht;
    
    EXPECT_TRUE(ht.isEmpty());
    
    ht.insert("key1", 100);
    ht.insert("key2", 200);
    
    EXPECT_FALSE(ht.isEmpty());
    EXPECT_EQ(ht.getSize(), 2);
    EXPECT_EQ(ht.get("key1"), 100);
    EXPECT_EQ(ht.get("key2"), 200);
    EXPECT_TRUE(ht.contains("key1"));
    EXPECT_FALSE(ht.contains("key3"));
}

TEST(HashTableTest, Remove) {
    HashTable<int, std::string> ht;
    
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(3, "three");
    
    EXPECT_TRUE(ht.remove(2));
    EXPECT_FALSE(ht.contains(2));
    EXPECT_EQ(ht.getSize(), 2);
    EXPECT_TRUE(ht.contains(1));
    EXPECT_TRUE(ht.contains(3));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    
    // Очищаем тестовые файлы
    std::remove("test_avl.txt");
    std::remove("test_array.txt");
    
    return result;
}
