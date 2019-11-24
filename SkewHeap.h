//
// Created by daniil on 24.11.2019.
//

#include <utility>

#ifndef PROJECTS_SKEWHEAP_H
#define PROJECTS_SKEWHEAP_H

#endif //PROJECTS_SKEWHEAP_H

class SkewNode {
public:
    int key;
    SkewNode *left = nullptr;
    SkewNode *right = nullptr;

    SkewNode(int key) {
        this->key = key;
    }
};

class SkewHeap {

public:
    SkewHeap(int key) {
        this->root = new SkewNode(key);
    }

    SkewHeap(SkewNode* node) {
        this->root = node;
    }

    void merge(SkewHeap heap) {
        root = merge(root, heap.root);
    }

    SkewNode* merge(SkewNode* node1, SkewNode* node2) {
        if (!node1)
            return node2;
        if (!node2)
            return node1;

        if (node1->key > node2->key)
            swap(node1, node2);

        swap(node1->left, node1->right);

        node1->left = merge(node2, node1->left);

        return node1;
    }

    void insert(int k) {
        merge(SkewHeap(k));
    }

    std::pair <int, SkewHeap> extractMin() {
        return std::make_pair(root->key, SkewHeap(merge(root->left, root->right)) );
    }


private:
    SkewNode* root;

    void swap(SkewNode* node1, SkewNode* node2) {
        SkewNode tmp = *node1;
        *node1 = *node2;
        *node2 = tmp;
    }
};