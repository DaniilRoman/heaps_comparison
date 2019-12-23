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
template<typename T>
static auto getBHeap = [](int param) { return new BHeap<T>(param, getVector<T>(n)); };
template<typename T>
auto BinomialHeap_ = [](int param) { return new BinomHeap<T>(getVector<T>(param)); };
template<typename T>
auto LeftistHeap_ = [](int param) { return new LeftistHeap<T>(getVector<T>(param)); };
template<typename T>
auto SkewHeap_ = [](int param) { return new SkewHeap<T>(getVector<T>(param)); };
template<typename T>
auto DHeap_ = [](int param) { return new BHeap<T>(55, getVector<T>(param)); };
template<typename T>
auto insert = [](AbstractHeap<T>* heap, AbstractHeap<T>* heap2) { heap->insert(getOperationValue<T>()); };
template<typename T>
auto removeFunc = [](AbstractHeap<T>* heap, AbstractHeap<T>* heap2) { heap->remove(getOperationValue<T>()); };
template<typename T>
auto deleteMin = [](AbstractHeap<T>* heap, AbstractHeap<T>* heap2) { heap->deleteMin(); };
template<typename T>
auto merge_ = [](AbstractHeap<T>* heap1, AbstractHeap<T>* heap2) { heap1->merge(heap2); };


template<typename T>
class Runner {

public:
    vector<int> dParam = { 2, 3, 5, 7, 10, 20, 33, 55, 100, 200, 300};//, 1001, 5000, 10000 };
//    vector<int> heapSizeParam = { 100, 1000, 10000, 50000, 100000, 500000, 1000000, 2000000, 5000000 };// , 10000000
    vector<int> heapSizeParam = { 100, 1000, 10000, 50000};// , 10000000
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
//        testRemoveBinomialHeap();
//        testDeleteMinBinomialHeap();
//        testMergeBinomialHeap();

        testInsertSkewHeap();
//        testRemoveSkewHeap();
//        testDeleteMinSkewHeap();
//        testMergeSkewHeap();

//        testInsertLeftistHeap();
//        testDeleteMinLeftistHeap();
//        testMergeLeftistHeap();
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

    void testMergeSkewHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, merge_<T>, SkewHeap_<T>, true);
        saveResultsToCSVWithHeader("merge_skew_heap", heapSizeParam, averages);
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

    void testMergeLeftistHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, merge_<T>, LeftistHeap_<T>, true);
        saveResultsToCSVWithHeader("merge_leftist_heap", heapSizeParam, averages);
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

    void testMergeBinomialHeap() {
        vector<float> averages = performAndGetAverages(heapSizeParam, merge_<T>, BinomialHeap_<T>, true);
        saveResultsToCSVWithHeader("merge_binomial_heap", heapSizeParam, averages);
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
    vector<float> performAndGetAverages(vector<int> params, Functor func, GetHeap getHeap, bool isMerge=false) {
        vector<vector<int>> results(params.size());

        for (int k = 0; k < repeatNumber; k++) {
            for (int i = 0; i < params.size(); i++) {
                AbstractHeap<T>* heap = getHeap(params[i]);
                AbstractHeap<T>* heapForMerge = nullptr;
                if (isMerge) {
                    heapForMerge = getHeap(1000);
                }

                auto start = std::chrono::high_resolution_clock::now();
                //+++++++++++++++++++
                func(heap, heapForMerge);
                //+++++++++++++++++++
                auto stop = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

                heap->destruct();
                delete heap;
                heap = nullptr;
                delete heapForMerge;
                heapForMerge = nullptr;
                results[i].push_back(duration);
                cout << duration << endl;
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

//        vector<int> vec = getVector(1);
//        BHeap<int> heap = BHeap<int>(5);
    BinomHeap<int> heap = BinomHeap<int>(3);
//        LeftistHeap<int> heap = LeftistHeap<int>(3);
//    SkewHeap<int> heap = SkewHeap<int>(3);
        heap.insert(4);
        heap.insert(5);
        heap.insert(2);
        heap.insert(20);
        heap.insert(88);
        heap.insert(33);
        heap.print();
        heap.insert(1);
        heap.print();
        heap.insert(95648);
        heap.print();
        heap.insert(35684);
        heap.print();
        heap.insert(11111);
        heap.print();
        heap.insert(32222);
        heap.print();
        heap.insert(99999);
        heap.print();
        heap.insert(4444);
        heap.print();
        heap.insert(3333);
        heap.print();
        heap.insert(2222);
        heap.print();
        heap.insert(48);
        heap.print();
        heap.insert(65);
        heap.print();
        heap.insert(55);
        heap.print();
        heap.insert(11);
        heap.print();
        heap.insert(2222);
        heap.print();
        heap.insert(48);
        heap.print();
        heap.insert(65);
        heap.print();
        heap.insert(55);
        heap.print();
        heap.insert(11);
        heap.print();
        heap.print();
        heap.insert(48);
        heap.print();
        heap.insert(65);
        heap.print();
        heap.insert(55);
        heap.print();
        heap.insert(11);
        heap.print();
        heap.destruct();

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
