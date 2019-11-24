//
// Created by daniil on 20.11.2019.
//

#ifndef PROJECTS_BINOMHEAP_H
#define PROJECTS_BINOMHEAP_H

#include <utility>
#include <vector>

class BinomHeapNode {
public:
    int key, degree;
    BinomHeapNode* parent = nullptr;
    BinomHeapNode* leftChild = nullptr;
    BinomHeapNode* rightChild = nullptr;
    BinomHeapNode* rightSibling = nullptr;

    BinomHeapNode(int key) {
        this->key = key;
        degree = 1;
    }

    BinomHeapNode(int key, int degree, BinomHeapNode* leftChild, BinomHeapNode* rightChild) {
        this->key = key;
        this->degree = degree;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }

    BinomHeapNode* getTree() {
        return new BinomHeapNode{key, degree, leftChild, rightChild};
    }

    void merge(BinomHeapNode* node) {
        if ( rightChild ) {
            rightChild->rightSibling = node;
        }
        if ( !leftChild ) {
            leftChild = rightChild;
        }
        rightChild = node;
        node->parent = this;
        this->degree++;
    }

    void decreaseKey(int delta) {
        key -= delta;
        BinomHeapNode* tmpParent = parent;
        while (tmpParent && tmpParent->key > key) {
            int parentKey = tmpParent->key;
            tmpParent->key = key;
            key = parentKey;
            tmpParent = tmpParent->parent;
        }
    }

    void clear() {
        rightSibling = nullptr;
    }

    void print() {
        std::cout << std::endl << "++++++++++++++++++++++++" << std::endl << "++++++++++++++++++++++++" << std::endl;
        BinomHeapNode* currentBrother = this;
        while(currentBrother) {
            BinomHeapNode* currentTree = currentBrother->leftChild;

            std::cout << "|" << currentBrother->key  << "|";
            if ( !currentBrother->leftChild && currentBrother->rightChild ) {
                std::cout << std::endl << "------ |" << currentBrother->rightChild->key << "|";

                std::cout << std::endl << "---------------------------------" << std::endl;
                currentBrother = currentBrother->rightSibling;
                continue;
            }
            while ( currentTree ) {
                BinomHeapNode* currentNode = currentTree;
                while (currentNode) {
                    std::cout << "|" << currentNode->key  << "|" << "----";
                    currentNode = currentNode->rightSibling;
                }
                std::cout << std::endl;

                if ( !currentTree->leftChild && currentTree->rightChild ) {
                    std::cout << "|" << currentTree->rightChild->key  << "|";
                    break;
                } else {
                    currentTree = currentTree->leftChild;
                }
            }
            std::cout << std::endl << "---------------------------------" << std::endl;
            currentBrother = currentBrother->rightSibling;
        }



    }
};


// --------------------------------------------------------------------------------


class BinomHeap {

public:

    BinomHeapNode* head{};

    explicit BinomHeap(BinomHeapNode* head) {
        this->head = head;
    }

    explicit BinomHeap(int x) {
        head = new BinomHeapNode(x);
    }

    BinomHeap() = default;

    void link(BinomHeapNode* node) {
        if (!head) {
            head = node;
        } else {
            head->rightSibling = node;
        }
    }

    void insert(int x) {
        if ( head == nullptr ) {
            head = new BinomHeapNode(x);
        } else {
            merge(BinomHeap(x));
        }
    }

    void merge(BinomHeap newHeap) {
        if ( head == nullptr ) {
            head = newHeap.head;
            return;
        }

        BinomHeap resultHeap = BinomHeap();

        BinomHeapNode* head1 = this->head;
        BinomHeapNode* head2 = newHeap.head;

        while (head1 || head2) {
            if ( head1 && head2) {
                if ( firstLessAndNotEqualResult(head1, head2, &resultHeap) ) {
                    resultHeap.link(head1);
                    head1 = head1->rightSibling;
                    continue;
                } else if ( firstLessAndNotEqualResult(head2, head1, &resultHeap) ) {
                    resultHeap.link(head2);
                    head2 = head2->rightSibling;
                    continue;
                }

                if ( equalDegree(head1, head2) ) {
                    BinomHeapNode* tree1 = head1->getTree();
                    BinomHeapNode* tree2 = head2->getTree();

                    tree1 = merge(tree1, tree2);

                    if ( equalDegree(tree1, resultHeap) ) {
                        resultHeap.head = merge(tree1, resultHeap.head);
                    } else {
                        resultHeap.link((tree1));
                    }

                    head1 = head1->rightSibling;
                    head2 = head2->rightSibling;
                    continue;
                }
            }
            if (head1) {
                if ( equalDegree(head1, resultHeap) ) {
                    resultHeap.head = merge(head1, resultHeap.head);
                } {
                    resultHeap.link(head1);
                }
                head1 = nullptr;
            }
            if (head2) {
                if ( equalDegree(head2, resultHeap) ) {
                    resultHeap.head = merge(head2, resultHeap.head);
                } {
                    resultHeap.link(head2);
                }
                head2 = nullptr;
            }
        }

        head = resultHeap.head;
    }

    BinomHeapNode* merge(BinomHeapNode* node1, BinomHeapNode* node2) {
        if ( node1->key <= node2->key ) {
            node1->merge(node2);
            return node1;
        } else {
            node2->merge(node1);
            return node2;
        }
    }

    std::pair <BinomHeapNode*, BinomHeapNode*> findMinAndPrev() {
        int min = head->key;
        BinomHeapNode* minHead = head;
        BinomHeapNode* prevMinHead = head;

        BinomHeapNode* prevHead = nullptr ;
        BinomHeapNode* currentHead = head;
        while (currentHead->rightSibling) {
            prevHead = currentHead;
            currentHead = currentHead->rightSibling;
            if ( min > currentHead->key ) {
                min = currentHead->key;
                minHead = currentHead;
                prevMinHead = prevHead;
            }
        }
        return std::make_pair(minHead, prevMinHead);
    }

    void deleteMin() {
        std::pair <BinomHeapNode*, BinomHeapNode*> mainPair = findMinAndPrev();
        if ( mainPair.second ) {
            mainPair.second->rightSibling = mainPair.first->rightSibling;
        } else {
            head = mainPair.first->rightSibling;
        }

        BinomHeap childrenHeap = BinomHeap(mainPair.first->leftChild);
        this->merge(childrenHeap);
    }

    void deleteNode(BinomHeapNode& node) {
        node.decreaseKey(INT16_MAX);
        deleteMin();
    }

    void print() {
        head->print();
    }

private:
    bool equalDegree(BinomHeapNode* node1, BinomHeap heap) {
        if (heap.head) {
            return node1->degree == heap.head->degree;
        } else {
            return false;
        }
    }

    bool equalDegree(BinomHeapNode* node1, BinomHeapNode* node2) {
        return node1->degree == node2->degree;
    }

    bool firstLessAndNotEqualResult(BinomHeapNode* head1, BinomHeapNode* head2, BinomHeap* heap) {
        return ( head1->degree < head2->degree )
               &&
               ( !heap->head || head1->degree != heap->head->degree );
    };

};




#endif //PROJECTS_BINOMHEAP_H
