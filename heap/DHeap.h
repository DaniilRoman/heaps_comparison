//
// Created by daniil on 04.11.2019.
//
#pragma once
#include <vector>

template<typename T>
class DHeap : public AbstractHeap<T>  {
public:

    std::vector<T> heap = {};

    int d;

    DHeap(int d, std::vector<T> heap) {
        this->d = d;
//        this->heap = heap;
        heap.reserve(heap.size()+1);
        makeHeap(heap);
    }

    ~DHeap() = default;

    void destruct() override {
    }

    void insert(T v) override {
        heap.push_back(v);
        emersion(last());
    }

    void remove(T value) override {
        for (int i=0; i<last(); i++) {
            if(value==heap[i]) {
                decreaseToMin(i);
                deleteMin();
                return;
            }
        }
        cout << "NOT DELETED" << endl;
    }

    T deleteMin() override {
        T min = heap[0];
        swap(0, last());
        heap.pop_back();
        diving(0);
        return min;
    }

    void merge(AbstractHeap<T>* heap) override {
        cout << "Not available on DHeap" << endl;
    }

    void print() {
        std::cout << "\n";
        for (int i = 0; i < last(); i++)
            std::cout << heap[i] << " ";
    }

private:
    int leftChild(int i) {
        int j = i * d + 1;

        if (j >= last()) {
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
            return std::min(j + d - 1, last());
        }
    }

    int minChild(int i) {
        int lc = leftChild(i);
        if (lc == -1) {
            return -1;
        }
        int rc = rightChild(i);
        int minIndex = lc;
        T minValue = getMaxValue<T>();

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
        T tmp = heap[i1];
        heap[i1] = heap[i2];
        heap[i2] = tmp;
    }

    void diving(int i) {
        int j1 = i;
        int j2 = minChild(i);
        while ( (j2 != -1) && (heap[j1]>heap[j2]) ) {
            swap(j1, j2);
            j1 = j2;
            j2 = minChild(j1);
        }
    }

    void emersion(int i) {
        int j1 = i;
        int j2 = parent(i);
        while ( (j2 != -1) && (heap[j1]<heap[j2]) ) {
            swap(j1, j2);
            j1 = j2;
            j2 = parent(j1);
        }
    }

    void decreaseToMin(int i) {
        heap[i] -= getMaxValue<T>();
        emersion(i);
    }

    void makeHeap(std::vector<T> heap) {
        for (int i=heap.size()-1; i>=0; i--) {
            insert(heap[i]);
        }
    }

    int last() {
        return heap.size()-1;
    }

};

