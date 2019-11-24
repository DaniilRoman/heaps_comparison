#include <iostream>
#include "BHeap.h"
#include "BinomHeap.h"

int main() {
//    BHeap* heap = new BHeap(3);
//
//    heap->print();
//    heap->makeHeap();
//    heap->print();
//    heap->insert(4);
//    heap->print();
//    heap->deleteBy(3);
//    heap->print();

    BinomHeap heap = BinomHeap(3);
    heap.print();
    heap.insert(4);
    heap.print();
    heap.insert(5);
    heap.print();
    heap.insert(2);
    heap.print();


    return 0;
}