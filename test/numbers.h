//
// Created by daniil on 30.11.2019.
//

#include <iostream>
#include <random>
#include <chrono>
#include "../heap/LeftistHeap.h"
#include "utils.h"
#include "../heap/BHeap.h"

using namespace std;

class Run {

public:
    int n = 100000;
    vector<int> vec = getVector(n);
    vector<int> dParam = {2, 3, 5, 7, 10, 20, 33, 55, 100, 1000, 5000, 10000};

    void runTest() {
        testDInBHeapInsert();
        testDInBHeapRemove();
        testDInBHeapDeleteMin();
        cout << " " << "END-END-END" << endl;
    }

    void testDInBHeapDeleteMin() {
        auto deleteMin = [](BHeap heap) { heap.deleteMin(); };
        vector<float> averages = performAndGetAverages(dParam, deleteMin);
        saveResultsToCSVWithHeader("d_param_delete_min", dParam, averages);
    }

    void testDInBHeapInsert() {
        auto insert = [](BHeap heap) { heap.insert(1000); };
        vector<float> averages = performAndGetAverages(dParam, insert);
        saveResultsToCSVWithHeader("d_param_insert", dParam, averages);
    }

    void testDInBHeapRemove() {
        auto remove = [](BHeap heap) { heap.remove(1000); };
        vector<float> averages = performAndGetAverages(dParam, remove);
        saveResultsToCSVWithHeader("d_param_remove", dParam, averages);
    }

    void saveResultsToCSVWithHeader(string name, vector<int> header, vector<float> values) {
        saveResultsToCSV(name, header);
        saveResultsToCSV(name, values);
    }

    template<typename Functor>
    vector<float> performAndGetAverages(vector<int> params, Functor func) {
        int repeatNumber = 1000;
        vector<vector<int>> results(params.size());

        for (int k = 0; k < repeatNumber; k++) {
            for (int i = 0; i < params.size(); i++) {
                BHeap heap = BHeap(params[i], vec);
                heap.makeHeap();
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