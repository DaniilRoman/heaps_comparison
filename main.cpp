#include <iostream>
#include "test/runner.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    /////////////////////////////

//    Runner<int> run = Runner<int>();
    Runner<vector<int>> run = Runner<vector<int>>();
    run.runTest();


    double vm, rss;
    processMemUsage(vm, rss);
    cout << "VM: " << vm << "; RSS: " << rss << endl;

    /////////////////////////////
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    std::cout << "DURATION: " << duration;

    return 0;
}

