//
// Created by Jovan Zivanovic on 7.7.25..
//

#include "Heap.h"

Heap::Heap(int n) {
    storage = new int[n];
    capacity = n;
    size = 0;
}
void Heap::makeCopy(const Heap &h) {
    capacity = h.capacity;
    size = h.size;
    if(!h.storage){
        storage = nullptr;
        return;
    }
    storage = new int[capacity];
    for(int i=0; i < capacity; i++) storage[i] = h.storage[i];
}

// can be made using heapify in O(N)
void Heap::makeHeap(int n){
    if (n < 1) return;
    if (n > capacity) n = capacity;
    size = 1;
    for(int i = 1; i < n; i++) insert(storage[i]);
}

void Heap:: insert(int key){
    if (size == capacity) throw "Container full";
    int f = father(size);
    int s = size++;
    while(s > 0 && storage[f] < key){
        storage[s] = storage[f];
        s = f;
        f = father(s);
    }
    storage[s] = key;
}

int Heap::peek() const {
    if (size == 0) throw "Container empty";
    return storage[0];
}

int Heap::deleteKey() {
    if (size == 0) throw "Container empty";
    int first = storage[0]; storage[0] = storage[--size];
    int f = 0;
    while(f < size - 1) {
        int s1 = leftSon(f), s2 = s1 + 1;
        if (s1 > size - 1) break;
        int x = s1, y = storage[s1];
        if (s2 <= size -1 && storage[s2] > y) {
            x = s2;
            y = storage[s2];
        }
        if (storage[f] >= y) break;
        storage[x] = storage[f];
        storage[f] = y;
        f = x;
    }
    return first;
}

void Heap::sort() {
    while(size>0){
        int first = deleteKey();
        storage[size] = first;
    }
}

std::ostream& operator<< (std::ostream& os, const Heap &heap) {
    for (int i = 0; i < heap.getSize(); i++) {
        os << heap.storage[i] << " ";
        if (i % 15 == 14) os << std::endl;
    }
    os << std::endl;
    return os;
}


