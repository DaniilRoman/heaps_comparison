//
// Created by daniil on 30.11.2019.
//

#include <vector>
#include <random>

#ifndef PROJECTS_UTILS_H
#define PROJECTS_UTILS_H

#endif //PROJECTS_UTILS_H

using namespace std;

vector<int> getVector(int n) {

    vector<int> array = {};

    mt19937 gen;
    uniform_int_distribution<> dis(1, n);

    for (int n=0; n<100; ++n) {
        array.push_back(dis(gen));
    }

    return array;
}
