//
// Created by daniil on 30.11.2019.
//

#include <vector>
#include <random>

#pragma once

using namespace std;


template <typename T>
vector<T> getVector(int n) {
    return NULL;
}

template <> vector<vector<int>> getVector(int n)   {
    vector<vector<int>> array = {};
    array.reserve(n+1);
    vector<int> array_ = {};

    mt19937 gen;
    uniform_int_distribution<> dis(1, 100000);
    for (int i=0; i<n; i++) {
        for (int i=0; i<3; i++) {
            array_.push_back(dis(gen));
        }
        array.push_back(array_);
        array_.clear();
    }
    array.push_back(vector<int> {1000, 1000, 1000});
    return array;
}

template <> vector<int> getVector(int n)   {
    vector<int> array = {};
    array.reserve(n+1);

    mt19937 gen;
    uniform_int_distribution<> dis(1, 100000);

    for (int i=0; i<n; i++) {
        array.push_back(dis(gen));
    }

    array.push_back(1000);
    return array;
}

template <typename T> T getMaxValue() { return NULL; }

template <> int getMaxValue<int>()   { return INT32_MAX; }

template <> vector<int> getMaxValue<vector<int>>()   { return vector<int> {INT32_MAX, INT32_MAX, INT32_MAX}; }

template <typename T> string type() { return NULL; }

template <> string type<int>()   { return "_[int]"; }

template <> string type<vector<int>>()   { return "_[vector<int>]"; }


template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << ", ";
    }
    os << "]\n";
    return os;
}

template <typename T>
vector<T> operator-(const vector<T>& v1, const vector<T>& v2)
{
    vector<T> result = {};
    result.reserve(v1.size());

    for(int i=0; i<v1.size(); i++) {
        result.push_back(v1[i]-v2[i]);
    }

    return result;
}

template <typename T>
vector<T> operator-=(const vector<T>& v1, const vector<T>& v2)
{
    vector<T> result = {};
    result.reserve(v1.size());

    for(int i=0; i<v1.size(); i++) {
        result.push_back(v1[i]-v2[i]);
    }

    return result;
}

template <typename T> T getOperationValue() { return NULL; }

template <> int getOperationValue<int>()   { return 1000; }

template <> vector<int> getOperationValue<vector<int>>()   { return vector<int> {1000, 1000, 1000}; }

template <typename T> T getInsertOperationValue() { return NULL; }

template <> int getInsertOperationValue<int>()   { return 2000; }

template <> vector<int> getInsertOperationValue<vector<int>>()   { return vector<int> {2000, 2000, 2000}; }
