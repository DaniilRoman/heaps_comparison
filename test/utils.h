//
// Created by daniil on 30.11.2019.
//

#include <vector>
#include <random>

#pragma once

using namespace std;

vector<int> getVector(int n) {

    vector<int> array = {};

    mt19937 gen;
    uniform_int_distribution<> dis(1, 100000);

    for (int i=0; i<n; i++) {
        array.push_back(dis(gen));
    }

    array.push_back(1000);
    return array;
}

template <typename T> T getMaxValue() { return INT16_MAX; }

template <> int getMaxValue<int>()   { return INT16_MAX; }
