//
// Created by daniil on 20.11.2019.
//

#ifndef PROJECTS_BINOMHEAP_H
#define PROJECTS_BINOMHEAP_H

#include <utility>
#include <vector>

using namespace std;

class BinomNode {
public:
    int key, degree;
    BinomNode *parent = nullptr;
    BinomNode *leftChild = nullptr;
    BinomNode *rightChild = nullptr;
    BinomNode *rightSibling = nullptr;

    BinomNode(int key) {
        this->key = key;
        degree = 1;
    }

    BinomNode(int key, int degree, BinomNode *leftChild, BinomNode *rightChild) {
        this->key = key;
        this->degree = degree;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
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

    void decreaseKey(int delta) {
        key -= delta;
        BinomNode *tmpParent = parent;
        while (tmpParent && tmpParent->key > key) {
            int parentKey = tmpParent->key;
            tmpParent->key = key;
            key = parentKey;
            tmpParent = tmpParent->parent;
        }
    }
};


// --------------------------------------------------------------------------------


class BinomHeap {

public:

    BinomNode *root{};

    explicit BinomHeap(BinomNode *root) {
        this->root = root;
    }

    explicit BinomHeap(int x) {
        root = new BinomNode(x);
    }

    BinomHeap() = default;

    BinomNode *link(BinomNode *from, BinomNode *to) {
        if (to) {
            to->rightSibling = from;
        } else {
            to = from;
            root = from;
        }
        return to;
    }

    void insert(int x) {
        if (root == nullptr) {
            root = new BinomNode(x);
        } else {
            merge(BinomHeap(x));
        }
    }

    void merge(BinomHeap newHeap) {
        if (root == nullptr) {
            root = newHeap.root;
            return;
        }

        BinomHeap resultHeap = BinomHeap();
        BinomNode *currentRoot = resultHeap.root;

        BinomNode *root1 = this->root;
        BinomNode *root2 = newHeap.root;

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
                    BinomNode *tree1 = root1->getTree();
                    BinomNode *tree2 = root2->getTree();

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
                    currentRoot = merge(root1, currentRoot);
                } else {
                    currentRoot = link(root1, currentRoot);
                }
                root1 = nullptr;
            }
            if (root2) {
                if (equalDegree(root2, currentRoot)) {
                    currentRoot = merge(root2, currentRoot);
                } else {
                    currentRoot = link(root2, currentRoot);
                }
                root2 = nullptr;
            }
        }
    }

    BinomNode *merge(BinomNode *node1, BinomNode *node2) {
        if (node1->key <= node2->key) {
            node1->merge(node2);
            return node1;
        } else {
            node2->merge(node1);
            return node2;
        }
    }

    void deleteMin() {
        pair<BinomNode *, BinomNode *> minAndPrev = findMinAndPrev();

        if (minAndPrev.second) {
            minAndPrev.second->rightSibling = minAndPrev.first->rightSibling;
        } else {
            root = minAndPrev.first->rightSibling;
        }

        if (minAndPrev.first->leftChild) {
            BinomHeap childrenHeap = BinomHeap(minAndPrev.first->leftChild);

            // delete parent links
            BinomNode *child = minAndPrev.first->leftChild;
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

    }

    void remove(int key) {
        decreaseKey(key, INT16_MAX);
        deleteMin();
    }

    void print() {
        print(root, "c");
        cout << endl << "++++++++++++++++++++++++++++" << endl;
    }

private:

    bool equalDegree(BinomNode *node1, BinomNode *node2) {
        if (node1 && node2) {
            return node1->degree == node2->degree;
        } else {
            return false;
        }
    }

    bool firstLessAndNotEqualResult(BinomNode *root1, BinomNode *root2, BinomNode *currentRoot) {
        return (root1->degree < root2->degree)
               &&
               (!currentRoot || root1->degree != currentRoot->degree);
    };


    void decreaseKey(int key, int delta) {
        findNodeByKey(root, key)->decreaseKey(delta);
    }

    BinomNode *findNodeByKey(BinomNode *node, int key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->key == key) {
            return node;
        }

        findNodeByKey(node->rightSibling, key);

        if (node->leftChild) {
            findNodeByKey(node->leftChild, key);
        } else {
            findNodeByKey(node->rightChild, key);
        }
    }


    pair<BinomNode *, BinomNode *> findMinAndPrev() {
        int min = root->key;
        BinomNode *minroot = root;
        BinomNode *prevMinroot = nullptr;

        BinomNode *prevroot = nullptr;
        BinomNode *currentRoot = root;
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

    void print(BinomNode *node, string str) {
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


#endif //PROJECTS_BINOMHEAP_H
