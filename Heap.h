//
// Created by Jovan Zivanovic on 7.7.25..
//

#ifndef DATA_STRUCTURES__HEAP_H
#define DATA_STRUCTURES__HEAP_H

#include <iostream>

class Heap {
public:
    explicit Heap(int n);
    Heap(int* keys, int n);
    Heap(const Heap& h);
    Heap(Heap&& h) noexcept;


    Heap& operator= (const Heap& h);
    Heap& operator= (Heap&& h) noexcept;

    ~Heap(){ clear(); }

    int getCapacity() const { return capacity; }
    int getSize() const { return size; }

    static void sort(int* arr, int n);

    void insert(int key);
    int peek() const;
    int deleteKey();


protected:
    void makeCopy(const Heap &h);
    void move(Heap& h);
    void clear();

    void makeHeap(int n);
    void makeHeap(){ makeHeap(capacity); }

    static int leftSon(int i) { return 2 * i + 1; }
    static int rightSon(int i) { return 2 * (i + 1); }
    static int father(int i) { return (i - 1) / 2; }

    void sort();

    friend std::ostream& operator<<(std::ostream& os, const Heap &h);



private:
    int* storage;
    int capacity;
    int size;


};

inline Heap::Heap(int* keys, int n){
    capacity = n;
    size = 0;
    storage = keys;
    makeHeap();
}

inline Heap::Heap(const Heap& h){
    makeCopy(h);
}

inline void Heap::move(Heap& h){
    storage = h.storage;
    capacity = h.capacity;
    size = h.size;

    h.storage = nullptr;
    h.capacity = h.size = 0;
}

inline Heap::Heap(Heap&& h) noexcept {
   move(h);
}

inline Heap& Heap::operator= (const Heap& h) {
    if (this != &h) {
        clear(); makeCopy(h);
    }
    return *this;
}

inline Heap& Heap::operator= (Heap&& h) noexcept {
    if (this != &h) {
        clear(); move(h);
    }
    return *this;
}
inline void Heap::sort(int *arr, int n) {
    Heap h(arr, n);
    h.sort();
    h.storage = nullptr;
}

inline void Heap::clear() {
    delete[] storage;
    storage = nullptr;
    capacity = size = 0;
}

#endif //DATA_STRUCTURES__HEAP_H
