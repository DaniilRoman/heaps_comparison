//
// Created by daniil on 24.11.2019.
//

#include <utility>
#include <iostream>

#ifndef PROJECTS_LEFTISTHEAP_H
#define PROJECTS_LEFTISTHEAP_H

#endif //PROJECTS_LEFTISTHEAP_H


class LeftistNode {
public:
    int key, dist;
    LeftistNode *left = nullptr;
    LeftistNode *right = nullptr;

    LeftistNode(int key) {
        this->key = key;
        dist = 0;
    }
};

class LeftistHeap {

public:
    LeftistHeap(int key) {
        this->root = new LeftistNode(key);
    }

    LeftistHeap(LeftistNode* node) {
        this->root = node;
    }

    void merge(LeftistHeap heap) {
        root = merge(root, heap.root);
    }

    LeftistNode* merge(LeftistNode* node1, LeftistNode* node2) {
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

    void insert(int k) {
        merge(LeftistHeap(k));
    }

    std::pair <int, LeftistHeap> extractMin() {
        return std::make_pair(root->key, LeftistHeap(merge(root->left, root->right)) );
    }

    void print() {
        print(root, "c");
        std::cout << std::endl << "++++++++++++++++++++++++++++" << std::endl;
    }


private:
    LeftistNode *root;

    void swap(LeftistNode* node1, LeftistNode* node2) {
        LeftistNode tmp = *node1;
        *node1 = *node2;
        *node2 = tmp;
    }


    void print(LeftistNode* node, std::string str) {
        if (node == nullptr)
            return;
        else {
            print(node->left, "l");
            std::cout << str+": " << node->key << "  ";
            print(node->right, "r");
        }
        return;
    }

};

