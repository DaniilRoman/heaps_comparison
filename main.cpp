#include <iostream>
#include "test/runner.h"

int main() {
//    BHeap  heap = BHeap(1000, getVector(2000000));
    auto start = std::chrono::high_resolution_clock::now();
    /////////////////////////////

    Runner run = Runner();
    run.runTest();
//    heap.insert(10000);


    /////////////////////////////
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    std::cout << "DURATION: " << duration;

    return 0;
}

