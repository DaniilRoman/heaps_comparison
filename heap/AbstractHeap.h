//
// Created by daniil on 19.12.2019.
//


#pragma once

template<typename T>
class AbstractHeap {
public:
    virtual ~AbstractHeap(){}

    virtual void insert(T value) = 0;
    virtual T deleteMin() = 0;
    virtual void remove(T value) = 0;
    virtual void merge(AbstractHeap<T>* heap) = 0;
};

