//
// Created by daniil on 04.11.2019.
//
#include <vector>
#ifndef PROJECTS_BHEAP_H
#define PROJECTS_BHEAP_H


class BHeap {
public:

    int n = 10;
    std::vector<int> heap = {1, 2, 5, 4, 3, 9, 8, 3, 77, 55};

    int d;

    BHeap(int d) {
        this->d = d;
    }

    void insert(int v) {
        n++;
        heap[n-1] = v;
        emersion(n-1);
    }

    void deleteBy(int i) {
        decreaseToMin(i);
        deleteMin();
    }

    void makeHeap() {
        for (int i=n-1; i>=0; i--) {
            diving(i);
        }
    }

    void print() {
        std::cout << "\n";
        for (int i = 0; i < n; i++)
            std::cout << heap[i] << " ";
    }

private:
    int leftChild(int i) {
        int j = i * d + 1;

        if (j >= n) {
            return -1;
        } else {
            return j;
        }
    }

    int rightChild(int i) {
        int j = leftChild(i);

        if (j == -1) {
            return -1;
        } else {
            return std::min(j + d - 1, n - 1);
        }
    }

    int minChild(int i) {
        int lc = leftChild(i);
        if (lc == -1) {
            return -1;
        }
        int rc = rightChild(i);
        int minIndex = n+1;
        int minValue = INT16_MAX;

        for (int idx=lc; idx<=rc; idx++) {
            if (heap[idx] < minValue) {
                minIndex = idx;
                minValue = heap[idx];
            }
        }

        return minIndex;
    }

    int parent(int i) {
        if (i == 0) {
            return -1;
        } else {
            return (i-1)/d;
        }
    }

    void swap(int i1, int i2) {
        int tmp = heap[i1];
        heap[i1] = heap[i2];
        heap[i2] = tmp;
    }

    void diving(int i) {
        int j1 = i;
        int j2 = minChild(i);
        while ( (j2 != -1) & (heap[j1]>heap[j2]) ) {
            swap(j1, j2);
            j1 = j2;
            j2 = minChild(j1);
        }
    }

    void emersion(int i) {
        int j1 = i;
        int j2 = parent(i);
        while ( (j2 != -1) & (heap[j1]<heap[j2]) ) {
            swap(j1, j2);
            j1 = j2;
            j2 = parent(j1);
        }
    }

    void decreaseToMin(int i) {
        heap[i] -= INT16_MAX;
        emersion(i);
    }

    void deleteMin() {
        swap(0, n-1);
        n--;
        heap.pop_back();
        diving(0);
    }

};


#endif //PROJECTS_BHEAP_H
