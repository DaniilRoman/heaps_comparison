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
    uniform_int_distribution<> dis(1, 100000);

    for (int i=0; i<n; i++) {
        array.push_back(dis(gen));
    }

    return array;
}
