#include <gtest/gtest.h>
#include "AVLTree.hpp"
#include "DynamicArray.hpp"
#include "SinglyLinkedList.hpp"
#include "Stack.hpp"
#include "Queue.hpp"
#include "HashTable.hpp"

// AVL Tree Tests
TEST(AVLTreeTest, InsertAndContains) {
    AVLTree tree;
    tree.insert("test");
    EXPECT_TRUE(tree.contains("test"));
    EXPECT_FALSE(tree.contains("nonexistent"));
}

TEST(AVLTreeTest, Remove) {
    AVLTree tree;
    tree.insert("a");
    tree.insert("b");
    tree.insert("c");
    
    tree.remove("b");
    EXPECT_FALSE(tree.contains("b"));
    EXPECT_TRUE(tree.contains("a"));
    EXPECT_TRUE(tree.contains("c"));
}

TEST(AVLTreeTest, Serialization) {
    AVLTree tree("TestTree");
    tree.insert("one");
    tree.insert("two");
    tree.insert("three");
    
    tree.serialize("test_tree.txt");
    
    AVLTree tree2;
    tree2.deserialize("test_tree.txt");
    
    EXPECT_TRUE(tree2.contains("one"));
    EXPECT_TRUE(tree2.contains("two"));
    EXPECT_TRUE(tree2.contains("three"));
    EXPECT_EQ(tree2.getName(), "TestTree");
}

// Dynamic Array Tests
TEST(DynamicArrayTest, PushAndAccess) {
    DynamicArray<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr.getSize(), 3);
}

TEST(DynamicArrayTest, InsertAndRemove) {
    DynamicArray<std::string> arr;
    arr.push_back("a");
    arr.push_back("c");
    
    arr.insert(1, "b");
    EXPECT_EQ(arr[0], "a");
    EXPECT_EQ(arr[1], "b");
    EXPECT_EQ(arr[2], "c");
    
    arr.remove(1);
    EXPECT_EQ(arr[0], "a");
    EXPECT_EQ(arr[1], "c");
}

// Singly Linked List Tests
TEST(SinglyLinkedListTest, BasicOperations) {
    SinglyLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_front(0);
    
    EXPECT_EQ(list.at(0), 0);
    EXPECT_EQ(list.at(1), 1);
    EXPECT_EQ(list.at(2), 2);
    EXPECT_EQ(list.getSize(), 3);
}

TEST(SinglyLinkedListTest, Find) {
    SinglyLinkedList<std::string> list;
    list.push_back("apple");
    list.push_back("banana");
    list.push_back("cherry");
    
    EXPECT_EQ(list.find("banana"), 1);
    EXPECT_EQ(list.find("nonexistent"), -1);
}

// Stack Tests
TEST(StackTest, PushPop) {
    Stack<int> stack;
    EXPECT_TRUE(stack.isEmpty());
    
    stack.push(10);
    stack.push(20);
    
    EXPECT_FALSE(stack.isEmpty());
    EXPECT_EQ(stack.top(), 20);
    
    stack.pop();
    EXPECT_EQ(stack.top(), 10);
}

// Queue Tests
TEST(QueueTest, EnqueueDequeue) {
    Queue<std::string> queue;
    queue.enqueue("first");
    queue.enqueue("second");
    
    EXPECT_EQ(queue.front(), "first");
    EXPECT_EQ(queue.back(), "second");
    
    queue.dequeue();
    EXPECT_EQ(queue.front(), "second");
}

// Hash Table Tests
TEST(HashTableTest, InsertGet) {
    HashTable<std::string, int> ht;
    ht.insert("key1", 100);
    ht.insert("key2", 200);
    
    EXPECT_EQ(ht.get("key1"), 100);
    EXPECT_EQ(ht.get("key2"), 200);
    EXPECT_TRUE(ht.contains("key1"));
    EXPECT_FALSE(ht.contains("key3"));
}

TEST(HashTableTest, Remove) {
    HashTable<int, std::string> ht;
    ht.insert(1, "one");
    ht.insert(2, "two");
    
    EXPECT_TRUE(ht.remove(1));
    EXPECT_FALSE(ht.contains(1));
    EXPECT_TRUE(ht.contains(2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
