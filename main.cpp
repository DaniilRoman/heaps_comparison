#include <iostream>
#include <algorithm>
#include "test/runner.h"

int main() {
//    AbstractHeap<int>*  heap = new SkewHeap<int>(getVector(10));

//    BHeap<int>  heap = BHeap<int>(1000, getVector(500000));
    auto start = std::chrono::high_resolution_clock::now();
    /////////////////////////////

//    AbstractHeap<int>* heap = new SkewHeap<int>(getVector(20000));
//    Runner<int> run = Runner<int>();
    Runner<vector<int>> run = Runner<vector<int>>();
    run.runTest();
//    run.dummyTest();

//    for(vector<int> arr : getVector<vector<int>>(5)) {
//        cout << arr << endl;
//    }



//    AbstractHeap<int>* heap1 = new LeftistHeap<int>(getVector(5));
//    AbstractHeap<int>* heap2 = new LeftistHeap<int>(getVector(5));
//    heap1->merge(heap2);


//    std::vector<int> v1 = {1, 2};
//    std::vector<int> v2 = {2, 3};
//    std::string s1 = "qqq";
//    std::string s2 = "a";
//    std::cout << (v1 > v2) << std::endl;


    /////////////////////////////
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
    std::cout << "DURATION: " << duration;

    return 0;
}

