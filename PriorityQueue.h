//
// Created by Jovan Zivanovic on 7.7.25..
//

#ifndef DATA_STRUCTURES__PRIORITYQUEUE_H
#define DATA_STRUCTURES__PRIORITYQUEUE_H

#include "Heap.h"

class PriorityQueue {
public:
    explicit PriorityQueue(int size) : heap(size) {};
    int gete() const { return heap.peek(); }
    int remove() { return heap.deleteKey(); }
    PriorityQueue& insert(int k) {
        heap.insert(k);
        return *this;
    }
    bool isEmpty() const { return heap.getSize() == 0; }
    bool isFull() const {
        return heap.getCapacity() == heap.getSize();
    }

private:
    Heap heap;
};


#endif //DATA_STRUCTURES__PRIORITYQUEUE_H
