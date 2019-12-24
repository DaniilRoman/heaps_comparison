//
// Created by daniil on 20.11.2019.
//

#pragma once
#include <utility>
#include <vector>
#include "AbstractHeap.h"
#include "../test/utils.h"

using namespace std;

template<typename T>
class BinomNode {
public:
    T key;
    int degree;
    BinomNode *parent = nullptr;
    BinomNode *leftChild = nullptr;
    BinomNode *rightChild = nullptr;
    BinomNode *rightSibling = nullptr;

    BinomNode(T key) {
        this->key = key;
        degree = 1;
    }

    BinomNode(T key, int degree, BinomNode *leftChild, BinomNode *rightChild) {
        this->key = key;
        this->degree = degree;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }

    ~BinomNode() = default;

    void destruct() {
        if(rightSibling) { rightSibling->destruct(); }
        if(leftChild) {
            leftChild->destruct();
            delete leftChild;
//            delete rightChild;
        } else if (rightChild) {
            rightChild->destruct();
            delete rightChild;
//            delete leftChild;
        }
      if(rightSibling) { delete rightSibling; }
//        delete parent;

        rightSibling = nullptr;
        parent = nullptr;
        rightChild = nullptr;
        leftChild = nullptr;
    }

    BinomNode *getTree() {
        return new BinomNode{key, degree, leftChild, rightChild};
    }

    void merge(BinomNode *node) {
        rightSibling = nullptr;
        node->rightSibling = nullptr;

        if (rightChild) {
            rightChild->rightSibling = node;
            if (!leftChild) {
                leftChild = rightChild;
            }
        }

        rightChild = node;
        node->parent = this;
        this->degree++;
    }

    void decreaseKey(T delta) {
        key -= delta;
        BinomNode *tmpParent = parent;
        while (tmpParent && tmpParent->key > key) {
            T parentKey = tmpParent->key;
            tmpParent->key = key;
            key = parentKey;
            tmpParent = tmpParent->parent;
        }
    }
};


// --------------------------------------------------------------------------------


template<typename T>
class BinomHeap : public AbstractHeap<T> {

public:

    BinomNode<T> *root{};

    BinomHeap(BinomNode<T> *root) {
        this->root = root;
    }

    BinomHeap(T x) {
        root = new BinomNode<T>(x);
    }

    BinomHeap(std::vector<T> values) {
        T startValue = values[values.size()-1];
        values.pop_back();
        root = new BinomNode<T>(startValue);
        for (T value : values) {
            insert(value);
        }
    }

    BinomHeap() {
        root = nullptr;
    };
    ~BinomHeap() = default;

    void destruct() override {
        root->destruct();
        delete root;
    }

    BinomNode<T> *link(BinomNode<T> *from, BinomNode<T> *to) {
        if (to) {
            to->rightSibling = from;
        } else {
            // when current root is null
            to = from;
            root = from;
        }
        return to;
    }

    void insert(T x) override {
        if (root == nullptr) {
            root = new BinomNode<T>(x);
        } else {
            merge(BinomHeap(x));
        }
    }

    void merge(AbstractHeap<T>* newHeap) override {
        merge(dynamic_cast<BinomHeap&>(*newHeap));
    }

    void merge(BinomHeap<T> newHeap) {
        if (root == nullptr) {
            root = newHeap.root;
            return;
        }

        BinomHeap resultHeap = BinomHeap();
        BinomNode<T> *currentRoot = resultHeap.root;

        BinomNode<T> *root1 = this->root;
        BinomNode<T> *root2 = newHeap.root;

        while (root1 || root2) {
            if (root1 && root2) {
                if (firstLessAndNotEqualResult(root1, root2, currentRoot)) {
                    currentRoot = link(root1, currentRoot);
                    root1 = root1->rightSibling;
                    continue;
                } else if (firstLessAndNotEqualResult(root2, root1, currentRoot)) {
                    currentRoot = link(root2, currentRoot);
                    root2 = root2->rightSibling;
                    continue;
                }
                if (equalDegree(root1, root2)) {
                    BinomNode<T> *tree1 = root1->getTree();
                    BinomNode<T> *tree2 = root2->getTree();

                    tree1 = merge(tree1, tree2);

                    if (equalDegree(tree1, currentRoot)) {
                        currentRoot = merge(tree1, currentRoot);
                    } else {
                        currentRoot = link(tree1, currentRoot);
                    }

                    root1 = root1->rightSibling;
                    root2 = root2->rightSibling;
                    continue;
                }
            }
            if (root1) {
                if (equalDegree(root1, currentRoot)) {
                    BinomNode<T> *tree1 = root1->getTree();
                    currentRoot = merge(tree1, currentRoot);
                    root1 = root1->rightSibling;
                } else {
                    currentRoot = link(root1, currentRoot);
                    root1 = nullptr;
                }
            }
            if (root2) {
                if (equalDegree(root2, currentRoot)) {
                    BinomNode<T> *tree2 = root2->getTree();
                    currentRoot = merge(tree2, currentRoot);
                    root2 = root2->rightSibling;
                } else {
                    currentRoot = link(root2, currentRoot);
                    root2 = nullptr;
                }
            }
        }
        root = currentRoot;
    }

    BinomNode<T> *merge(BinomNode<T> *node1, BinomNode<T> *node2) {
        if (node1->key <= node2->key) {
            node1->merge(node2);
            return node1;
        } else {
            node2->merge(node1);
            return node2;
        }
    }

    T deleteMin() override {
        pair<BinomNode<T> *, BinomNode<T> *> minAndPrev = findMinAndPrev();

        if (minAndPrev.second) {
            minAndPrev.second->rightSibling = minAndPrev.first->rightSibling;
        } else {
            root = minAndPrev.first->rightSibling;
        }

        if (minAndPrev.first->leftChild) {
            BinomHeap childrenHeap = BinomHeap(minAndPrev.first->leftChild);

            // delete parent links
            BinomNode<T> *child = minAndPrev.first->leftChild;
            while (child) {
                child->parent = nullptr;
                child = child->rightSibling;
            }
            this->merge(childrenHeap);
        } else {
            BinomHeap childrenHeap = BinomHeap(minAndPrev.first->rightChild);
            minAndPrev.first->rightChild->parent = nullptr;
            this->merge(childrenHeap);
        }

        return minAndPrev.first->key;
    }

    void remove(T key) override {
        decreaseKey(key, getMaxValue<T>());
        deleteMin();
    }

    void print() {
        print(root, "c");
        cout << endl << "++++++++++++++++++++++++++++" << endl;
    }

private:

    bool equalDegree(BinomNode<T> *node1, BinomNode<T> *node2) {
        if (node1 && node2) {
            return node1->degree == node2->degree;
        } else {
            return false;
        }
    }

    bool firstLessAndNotEqualResult(BinomNode<T> *root1, BinomNode<T> *root2, BinomNode<T> *currentRoot) {
        return (root1->degree < root2->degree)
               &&
               (!currentRoot || root1->degree != currentRoot->degree);
    };


    void decreaseKey(T key, T delta) {
        findNodeByKey(root, key)->decreaseKey(delta);
    }

    BinomNode<T> *findNodeByKey(BinomNode<T> *node, T key) {
//        if (node == nullptr) {
//            return nullptr;
//        }
//
//        if (node->key == key) {
//            return node;
//        }
//
//        if (node->rightSibling) {
//            findNodeByKey(node->rightSibling, key);
//        }
//        if (node->leftChild) {
//            findNodeByKey(node->leftChild, key);
//        } else if (node->leftChild) {
//            findNodeByKey(node->rightChild, key);
//        }

        if(node != nullptr){
            if(node->key == key){
                return node;
            } else {
                BinomNode<T>* foundNode = nullptr;
                if (node->rightSibling) {
                    foundNode = findNodeByKey(node->rightSibling, key);
                }
                if(foundNode == nullptr && node->rightChild) {
                    foundNode = findNodeByKey(node->rightChild, key);
                }
                if(foundNode == nullptr && node->leftChild) {
                    foundNode = findNodeByKey(node->leftChild, key);
                }
                return foundNode;
            }
        } else {
            return nullptr;
        }
    }


    pair<BinomNode<T> *, BinomNode<T> *> findMinAndPrev() {
        T min = root->key;
        BinomNode<T> *minroot = root;
        BinomNode<T> *prevMinroot = nullptr;

        BinomNode<T> *prevroot = nullptr;
        BinomNode<T> *currentRoot = root;
        while (currentRoot->rightSibling) {
            prevroot = currentRoot;
            currentRoot = currentRoot->rightSibling;
            if (min > currentRoot->key) {
                min = currentRoot->key;
                minroot = currentRoot;
                prevMinroot = prevroot;
            }
        }
        return make_pair(minroot, prevMinroot);
    }

    void print(BinomNode<T> *node, string str) {
        if (node == nullptr) {
            return;
        } else {
            print(node->rightSibling, "b");
            cout << endl;
            if (node->leftChild) {
                print(node->leftChild, "l");
            } else {
                print(node->rightChild, "r");
            }
            cout << str + ": " << node->key << "  ";
        }
        return;
    }

};
