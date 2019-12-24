//
// Created by daniil on 24.11.2019.
//

#include <utility>
#include <iostream>
#include "AbstractHeap.h"

template <typename T>
class LeftistNode {
public:
    T key;
    int dist;
    LeftistNode *left = nullptr;
    LeftistNode *right = nullptr;

    LeftistNode(T key) {
        this->key = key;
        dist = 0;
    }

    void destruct() {
        if(right) { right->destruct(); }
        if(left) { left->destruct(); }
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
    }

    ~LeftistNode() = default;
};

template <typename T>
class LeftistHeap : public AbstractHeap<T> {

public:
    LeftistHeap(T key) {
        this->root = new LeftistNode<T>(key);
    }

    LeftistHeap(LeftistNode<T>* node) {
        this->root = node;
    }

    LeftistHeap(std::vector<T> values) {
        T startValue = values[values.size()-1];
        values.pop_back();
        root = new LeftistNode<T>(startValue);
        for (T value : values) {
            insert(value);
        }
    }

    LeftistHeap() = default;
    ~LeftistHeap() = default;

    void destruct() override {
        root->destruct();
        delete root;
    }

    void merge(AbstractHeap<T>* newHeap) override {
        merge(dynamic_cast<LeftistHeap&>(*newHeap));
    }

    void merge(LeftistHeap heap) {
        root = merge(root, heap.root);
    }

    LeftistNode<T>* merge(LeftistNode<T>* node1, LeftistNode<T>* node2) {
        if (node1 == nullptr) {
            return node2;
        }
        if (node2 == nullptr) {
            return node1;
        }
        if (node2->key < node1->key) {
            swap(node1, node2);
        }
        node1->right = merge(node1->right, node2);

        if (node1->left == nullptr) {
            node1->left = node1->right;
            node1->right = nullptr;
        } else {
            if ( node1->left->dist < node1->right->dist ) {
                swap(node1->left, node1->right);
            }

            node1->dist = node1->right->dist + 1;
        }

        return node1;
    }

    void insert(T k) override {
        merge(LeftistHeap(k));
    }

    T deleteMin() override {
        T minValue = root->key;
        root = merge(root->left, root->right);
        return minValue;
    }

    void remove(T value) override { }

    void print() {
        print(root, "c");
        std::cout << std::endl << "++++++++++++++++++++++++++++" << std::endl;
    }


private:
    LeftistNode<T> *root;

    void swap(LeftistNode<T>* node1, LeftistNode<T>* node2) {
        LeftistNode<T> tmp = *node1;
        *node1 = *node2;
        *node2 = tmp;
    }


    void print(LeftistNode<T>* node, std::string str) {
        if (node == nullptr)
            return;
        else {
            print(node->left, "l");
            print(node->right, "r");
            std::cout << str+": " << node->key << "  ";
        }
        return;
    }

};

