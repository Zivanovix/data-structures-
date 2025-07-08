
#ifndef HEAPS_FIBONACCIHEAP_H
#define HEAPS_FIBONACCIHEAP_H

struct node{
    int priority;
    int degree;
    int lvl;
    node *left, *right, *parent, *child;
};

class FibonacciHeap {

public:
    FibonacciHeap(bool isMin=true);

    node* create_node(int val);
    node* extract();

    void insert(int val);
    void display();
    void consolidate();
    void fibHeapLink(node* y, node* x);

    bool compare(int a, int b);
    bool isEmpty();
    int getSize();
    void clear();

private:
    int nodeCount;
    node *heapRoot;
    bool isMin;
};


#endif //HEAPS_FIBONACCIHEAP_H
