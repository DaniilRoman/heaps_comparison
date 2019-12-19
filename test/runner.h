//
// Created by daniil on 30.11.2019.
//

#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include "../heap/LeftistHeap.h"
#include "utils.h"
#include "../heap/BHeap.h"
#include "../heap/AbstractHeap.h"

using namespace std;

static int n = 100000;
static vector<int> vec = getVector(n);
static auto getBHeap = [](int param) { return BHeap(param, vec); };

class Runner {

public:
    vector<int> dParam = {2, 3, 5, 7, 10, 20, 33, 55, 100, 1000, 5000, 10000};
    vector<int> heapSizeParam = {100, 1000, 10000, 50000, 100000, 500000, 1000000};
//    vector<int> heapSizeParam = { 1000000, 500000, 100000, 50000, 10000, 1000, 100 };

    void runTest() {
//        testDInBHeapInsert();
//        testDInBHeapRemove();
//        testDInBHeapDeleteMin();
//        testInsertBHeap();
//        testRemoveBHeap();
//        testDeleteMinBHeap();
        cout << " " << "END-END-END" << endl;
    }

    void testInsertBHeap() {
        auto insert = [](BHeap heap) { heap.insert(1000); };
        auto getHeap = [](int param) { return BHeap(1000, getVector(param)); };
        vector<float> averages = performAndGetAverages(heapSizeParam, insert, getHeap);
        saveResultsToCSVWithHeader("insert_d_heap", heapSizeParam, averages);
    }

    void testRemoveBHeap() {
        auto remove = [](BHeap heap) { heap.remove(1000); };
        auto getHeap = [](int param) { return BHeap(1000, getVector(param)); };
        vector<float> averages = performAndGetAverages(heapSizeParam, remove, getHeap);
        saveResultsToCSVWithHeader("remove_d_heap", heapSizeParam, averages);
    }

    void testDeleteMinBHeap() {
        auto deleteMin = [](AbstractHeap<T> heap) { heap.deleteMin(); };
        auto getHeap = [](int param) { return BHeap(1000, getVector(param)); };
        vector<float> averages = performAndGetAverages(heapSizeParam, deleteMin, getHeap);
        saveResultsToCSVWithHeader("delete_min_d_heap", heapSizeParam, averages);
    }

    void testDInBHeapDeleteMin() {
        auto deleteMin = [](BHeap heap) { heap.deleteMin(); };
        vector<float> averages = performAndGetAverages(dParam, deleteMin, getBHeap);
        saveResultsToCSVWithHeader("d_param_delete_min", dParam, averages);
    }

    void testDInBHeapInsert() {
        auto insert = [](BHeap heap) { heap.insert(1000); };
        vector<float> averages = performAndGetAverages(dParam, insert, getBHeap);
        saveResultsToCSVWithHeader("d_param_insert", dParam, averages);
    }

    void testDInBHeapRemove() {
        auto remove = [](BHeap heap) { heap.remove(1000); };
        vector<float> averages = performAndGetAverages(dParam, remove, getBHeap);
        saveResultsToCSVWithHeader("d_param_remove", dParam, averages);
    }

    void saveResultsToCSVWithHeader(string name, vector<int> header, vector<float> values) {
        saveResultsToCSV(name, header);
        saveResultsToCSV(name, values);
    }

    template<typename Functor, typename GetHeap>
    vector<float> performAndGetAverages(vector<int> params, Functor func, GetHeap getHeap) {
        int repeatNumber = 1000;
        vector<vector<int>> results(params.size());

        for (int k = 0; k < repeatNumber; k++) {
            for (int i = 0; i < params.size(); i++) {
                BHeap heap = getHeap(params[i]);
//                heap.makeHeap();
                /////////////////////
                auto start = std::chrono::high_resolution_clock::now();

                //+++++++++++++++++++
                func(heap);
                //+++++++++++++++++++

                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

                results[i].push_back(duration);
            }
        }

        vector<float> averages = {};
        for (vector<int> result: results) {
            float average = accumulate(result.begin(), result.end(), 0.0) / result.size();
            averages.push_back(average);
        }

        return averages;
    }

    template<class T>
    void saveResultsToCSV(string name, vector<T> values) {
        fstream fout;

        fout.open(".././results/" + name + ".csv", ios::out | ios::app);

        for (int i = 0; i < values.size(); i++) {
            fout << values[i];
            if (i < values.size() - 1) {
                fout << ", ";
            }
        }

        fout << "\n";
    }

    int testNumbers() {
        /////////////////////
        vector<int> vec = getVector(n);

        BHeap heap = BHeap(20, vec);
        heap.makeHeap();
        /////////////////////
        auto start = std::chrono::high_resolution_clock::now();

        //+++++++++++++++++++
        heap.insert(1000);
        //+++++++++++++++++++

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        cout << " " << duration;

        return 0;
    }


    void dummyTest() {
        //    BHeap* heap = new BHeap(3);
//
//    heap->print();
//    heap->makeHeap();
//    heap->print();
//    heap->insert(4);
//    heap->print();
//    heap->remove(3);
//    heap->print();


//    BinomHeap heap = BinomHeap(3);
        LeftistHeap heap = LeftistHeap(3);
//    SkewHeap heap = SkewHeap(3);
        heap.print();
        heap.insert(4);
        heap.print();
        heap.insert(5);
        heap.print();
        heap.insert(2);
        heap.print();
//    heap.remove(3);
//    heap.print();

//    heap.deleteMin();
//    heap.print();
//    heap.deleteMin();
//    heap.print();
//    heap.deleteMin();
//    heap.print();
    }

};
