//
// Created by daniil on 24.11.2019.
//

#include <utility>
#include <iostream>
#include <vector>
#include "AbstractHeap.h"

template <typename T>
class SkewNode {
public:
    T key;
    SkewNode *left = nullptr;
    SkewNode *right = nullptr;

    SkewNode(T key) {
        this->key = key;
    }
};

template <typename T>
class SkewHeap : public AbstractHeap<T> {

public:
    SkewHeap(T key) {
        this->root = new SkewNode<T>(key);
    }

    SkewHeap(SkewNode<T> *node) {
        this->root = node;
    }

    SkewHeap(std::vector<T> values) {
        T startValue = values[values.size()];
        values.pop_back();
        root = new SkewNode<T>(startValue);
        for (T value : values) {
            insert(value);
        }
    }

    SkewHeap() = default;
    ~SkewHeap() = default;

    void merge(AbstractHeap<T>* newHeap) override {
        merge(dynamic_cast<SkewHeap&>(*newHeap));
    }

    void merge(SkewHeap heap) {
        root = merge(root, heap.root);
    }

    SkewNode<T> *merge(SkewNode<T>* node1, SkewNode<T>* node2) {
        if (!node1) {
            return node2;
        }
        if (!node2) {
            return node1;
        }

        if (node1->key <= node2->key) {
            SkewNode<T>* tempHeap = node1->right;
            node1->right = node1->left;
            node1->left = merge(node2, tempHeap);
            return node1;
        } else {
            return merge(node2, node1);
        }

    }

    void insert(T k) override {
        merge(SkewHeap(k));
    }

    void remove(T key) override {
        remove(root, key);
    }

    T deleteMin() override {
        T minValue = root->key;
        root = merge(root->left, root->right);
        return minValue;
    }

    void print() {
        print(root, "c");
        std::cout << std::endl << "++++++++++++++++++++++++++++" << std::endl;
    }


private:
    SkewNode<T> *root;

    SkewNode<T> *remove(SkewNode<T> *node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->left && node->left->key == key) {
            node->left = merge(node->left->left, node->left->right);
            return node;
        }
        if (node->right && node->right->key == key) {
            node->right = merge(node->right->left, node->right->right);

            return node;
        }
        remove(node->left, key);
        remove(node->right, key);
    }

    void print(SkewNode<T> *node, std::string str) {
        if (node == nullptr) {
            return;
        } else {
            print(node->left, "l");
            print(node->right, "r");
            std::cout << str + ": " << node->key << "  ";
        }
        return;
    }

};