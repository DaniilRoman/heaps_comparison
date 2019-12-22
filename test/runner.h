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
#include "../heap/BinomHeap.h"
#include "../heap/SkewHeap.h"

#pragma once

using namespace std;

static int n = 1000000;
static vector<int> vec = getVector(n);
template<typename T>
static auto getBHeap = [](int param) { return new BHeap<T>(param, vec); };
template<typename T>
auto BinomialHeap_ = [](int param) { return new BinomHeap<T>(getVector(param)); };
template<typename T>
auto LeftistHeap_ = [](int param) { return new LeftistHeap<T>(getVector(param)); };
template<typename T>
auto SkewHeap_ = [](int param) { return new SkewHeap<T>(getVector(param)); };
template<typename T>
auto DHeap_ = [](int param) { return new BHeap<T>(55, getVector(param)); };
template<typename T>
auto insert = [](AbstractHeap<T>* heap) { heap->insert(1000); };
template<typename T>
auto removeFunc = [](AbstractHeap<T>* heap) { heap->remove(1000); };
template<typename T>
auto deleteMin = [](AbstractHeap<T>* heap) { heap->deleteMin(); };


template<typename T>
class Runner {

public:
    vector<int> dParam = {2, 3, 5, 7, 10, 20, 33, 55, 100, 1000, 5000, 10000};
    vector<int> heapSizeParam = {100, 1000, 10000, 50000};// , 5000000, 10000000
//    , 100000, 500000, 1000000
    int repeatNumber = 10;
//    vector<int> heapSizeParam = { 1000000, 500000, 100000, 50000, 10000, 1000, 100 };

    void runTest() {
//        testDInBHeapInsert();
//        testDInBHeapRemove();
//        testDInBHeapDeleteMin();

//        testInsertBHeap();
//        testRemoveBHeap();
//        testDeleteMinBHeap();

//        testInsertBinomialHeap();
        testRemoveBinomialHeap();
//        testDeleteMinBinomialHeap();

//        testInsertSkewHeap();
//        testRemoveSkewHeap();
//        testDeleteMinSkewHeap();

//        testInsertLeftistHeap();
//        testDeleteMinLeftistHeap();
        cout << " " << "END-END-END" << endl;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void testInsertSkewHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, insert<T>, SkewHeap_<T>);
        saveResultsToCSVWithHeader("insert_skew_heap", heapSizeParam, averages);
    }

    void testRemoveSkewHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, removeFunc<T>, SkewHeap_<T>);
        saveResultsToCSVWithHeader("remove_skew_heap", heapSizeParam, averages);
    }

    void testDeleteMinSkewHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, deleteMin<T>, SkewHeap_<T>);
        saveResultsToCSVWithHeader("delete_min_skew_heap", heapSizeParam, averages);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void testInsertLeftistHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, insert<T>, LeftistHeap_<T>);
        saveResultsToCSVWithHeader("insert_leftist_heap", heapSizeParam, averages);
    }

    void testDeleteMinLeftistHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, deleteMin<T>, LeftistHeap_<T>);
        saveResultsToCSVWithHeader("delete_min_leftist_heap", heapSizeParam, averages);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void testInsertBinomialHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, insert<T>, BinomialHeap_<T>);
        saveResultsToCSVWithHeader("insert_binomial_heap", heapSizeParam, averages);
    }

    void testRemoveBinomialHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, removeFunc<T>, BinomialHeap_<T>);
        saveResultsToCSVWithHeader("remove_binomial_heap", heapSizeParam, averages);
    }

    void testDeleteMinBinomialHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, deleteMin<T>, BinomialHeap_<T>);
        saveResultsToCSVWithHeader("delete_min_binomial_heap", heapSizeParam, averages);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void testInsertBHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, insert<T>, DHeap_<T>);
        saveResultsToCSVWithHeader("insert_d_heap", heapSizeParam, averages);
    }

    void testRemoveBHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, removeFunc<T>, DHeap_<T>);
        saveResultsToCSVWithHeader("remove_d_heap", heapSizeParam, averages);
    }

    void testDeleteMinBHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, deleteMin<T>, DHeap_<T>);
        saveResultsToCSVWithHeader("delete_min_d_heap", heapSizeParam, averages);
    }

    // -----------------------------------

    void testDInBHeapDeleteMin() {
        vector<float> averages = performAndGetAverages(dParam, deleteMin<T>, getBHeap<T>);
        saveResultsToCSVWithHeader("d_param_delete_min", dParam, averages);
    }

    void testDInBHeapInsert() {
        vector<float> averages = performAndGetAverages(dParam, insert<T>, getBHeap<T>);
        saveResultsToCSVWithHeader("d_param_insert", dParam, averages);
    }

    void testDInBHeapRemove() {
        vector<float> averages = performAndGetAverages(dParam, removeFunc<T>, getBHeap<T>);
        saveResultsToCSVWithHeader("d_param_remove", dParam, averages);
    }


private :

    template<typename Functor, typename GetHeap>
    vector<float> performAndGetAverages(vector<int> params, Functor func, GetHeap getHeap) {
        vector<vector<int>> results(params.size());

        for (int k = 0; k < repeatNumber; k++) {
            for (int i = 0; i < params.size(); i++) {
                AbstractHeap<T>* heap = getHeap(params[i]);

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

    void saveResultsToCSVWithHeader(string name, vector<int> header, vector<float> values) {
        remove(string(getFilePath(name)).c_str());
        saveResultsToCSV(name, header);
        saveResultsToCSV(name, values);
    }

    template<class R>
    void saveResultsToCSV(string name, vector<R> values) {
        fstream fout;

        fout.open(getFilePath(name), ios::out | ios::app);

        for (int i = 0; i < values.size(); i++) {
            fout << values[i];
            if (i < values.size() - 1) {
                fout << ", ";
            }
        }

        fout << "\n";
    }

    string getFilePath(string fileName) {
        return ".././results/" + fileName + ".csv";
    }

public:

    void dummyTest() {
//        BHeap* heap = new BHeap(3);
//
//    heap->print();
//    heap->makeHeap();
//    heap->print();
//    heap->insert(4);
//    heap->print();
//    heap->remove(3);
//    heap->print();


    BinomHeap<int> heap = BinomHeap<int>(3);
//        LeftistHeap heap = LeftistHeap<int>(3);
//    SkewHeap heap = SkewHeap(3);
        heap.print();
        heap.insert(4);
        heap.print();
        heap.insert(5);
        heap.print();
        heap.insert(2);
        heap.print();
        heap.insert(20);
        heap.print();
        heap.insert(88);
        heap.print();
        heap.insert(33);
        heap.print();
        heap.insert(1);
        heap.print();

        cout  << endl << "end;" << endl;

//    heap.remove(3);
//    heap.print();
//
//    heap.deleteMin();
//    heap.print();
//    heap.deleteMin();
//    heap.print();
//    heap.deleteMin();
//    heap.print();
    }

};