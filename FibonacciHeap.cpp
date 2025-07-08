
#include "FibonacciHeap.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>


FibonacciHeap::FibonacciHeap(bool isMin) {
    heapRoot = nullptr;
    nodeCount = 0;
    this->isMin = isMin;
}

node* FibonacciHeap::create_node(int val) {
    node *newNode = new node;
    newNode->priority = val;
    return newNode;
}

void FibonacciHeap::insert(int val) {
    node *newNode = create_node(val);

    newNode->parent = nullptr;
    newNode->child = nullptr;
    newNode->degree = 0;
    newNode->left = newNode;
    newNode->right = newNode;
    newNode->lvl = 0;

    if(heapRoot) {
        (heapRoot->left)->right = newNode;
        newNode->right = heapRoot;
        newNode->left = heapRoot->left;
        heapRoot->left = newNode;

        if(compare(newNode->priority, heapRoot->priority)){
            heapRoot = newNode;
        }
    }else{
        heapRoot = newNode;
    }
    nodeCount++;
}

void FibonacciHeap::display(){
    bool ind = false;
    std::queue<node*> q;
    node *p = heapRoot;
    node *prevParent = nullptr;
    int prevLvl = 0;
    if(!p){
        std::cout << "The heap is empty" << std::endl;
        return;
    }

    std::cout << " ";
    do{
        std::cout << p->priority << " ";
        node *c = p->child;
        p->lvl = 0;
        if(c) {
            do {
                c->lvl = 1;
                q.push(c);
                c = c->right;
            } while (c != p->child);
        }
        p = p->right;
    }while(p != heapRoot);

    while(!q.empty()){
        node *next = q.front();
        q.pop();
        int currLvl = next->lvl;
        node* currParent = next->parent;
        if(currLvl != prevLvl){
            ind = false;
            std::cout << std::endl;
        }
        if(currParent != prevParent){
            if(ind){
                std::cout << " ";
            }
            std::cout << "|" << next->parent->priority << "|";
            ind = true;
        }
        std::cout << " " << next->priority;
        node *c = next->child;
        if(c) {
            do {
                c->lvl = next->lvl+1;
                q.push(c);
                c = c->right;
            } while (c != next->child);
        }
        prevLvl = currLvl;
        prevParent = currParent;
    }
}



node* FibonacciHeap::extract() {
    node *ext, *curr;
    ext = heapRoot;

    if(!heapRoot) {
        std::cout << std::endl << "The heap is empty" << std::endl;
        return heapRoot;
    }

    if(heapRoot->child){
        curr = heapRoot->child;
        for(int i = 0; i < heapRoot->degree; i++){
            node *next = curr->right;
            (heapRoot->left)->right = curr;
            curr->right = heapRoot;
            curr->left = heapRoot->left;
            heapRoot->left = curr;

            curr->parent = nullptr;
            curr->lvl = 0;
            curr = next;
        }
    }

    //unlink the one with most priority
    (ext->left)->right = ext->right;
    (ext->right)->left = ext->left;
    heapRoot = ext->right;

    if(ext == heapRoot){
        heapRoot = nullptr;
    }
    else{
        consolidate();
    }
    nodeCount--;
    return ext;
}
void FibonacciHeap::consolidate() {
    if (!heapRoot)
        return;

    // 1) Make a snapshot of rootList (collect all roots in one vector)
    std::vector<node*> rootList;

    node* w = heapRoot;
    do {
        rootList.push_back(w);
        w = w->right;
    } while (w != heapRoot);

    //this is maximal degree in Fibonacci heap
    int D = (int)std::floor(std::log2(nodeCount)) + 2;


    // Vector A where each element represents a subTree in heap that has degree equal to its index in A
    std::vector<node*> A(D, nullptr);

    // 3) Iterate through rootList
    for (node* x : rootList) {

        int d = x->degree;

        // While there is a subtree of degree d that we have already visited, merge
        while (A[d] != nullptr) {
            node* y = A[d];

            if (!compare(x->priority, y->priority)) {
                std::swap(x, y);
            }
            // Merge y in x (y becomes a child of x)
            fibHeapLink(y, x);
            A[d] = nullptr;
            d++;
        }
        // After merge, now we have root x of degree d
        A[d] = x;
    }

    // 4) Reconstruct root list and find a new min/max element

    heapRoot = nullptr;
    for (node* root : A) {
        if (root != nullptr) {

            root->parent = nullptr;
            root->lvl = 0;
            root->left = root;
            root->right = root;

            // if root is the first element in new list
            if (!heapRoot) {
                heapRoot = root;
            } else {
                // insert root next to heapRoot to make double-linked circular list
                root->left = heapRoot->left;
                root->right = heapRoot;
                heapRoot->left->right = root;
                heapRoot->left = root;

                // check for heapRoot update
                if (compare(root->priority, heapRoot->priority)) {
                    heapRoot = root;
                }
            }
        }
    }
}
void FibonacciHeap::fibHeapLink(node* y, node* x) {
    // 1) Delete y from rootList
    y->left->right = y->right;
    y->right->left = y->left;

    // 2) Y is child of x
    y->parent = x;
    y->lvl = x->lvl + 1;

    if (x->child == nullptr) {
        // x has no more children
        x->child = y;
        y->left  = y;
        y->right = y;
    } else {
        // insert y in x's child list
        node* c = x->child;

        y->left  = c->left;
        y->right = c;
        c->left->right = y;
        c->left = y;
    }

    // 3) Ažuriramo stepen x-a
    x->degree++;
}

bool FibonacciHeap::compare(int a, int b) {
    if(isMin){
        return a < b;
    }
    return a > b;
}

bool FibonacciHeap::isEmpty() {
    return heapRoot == nullptr;
}

int FibonacciHeap::getSize() {
    return nodeCount;
}

void FibonacciHeap::clear() {

    std::queue<node*> q;
    node* p = heapRoot;
    if(!p){
        return;
    }
    do{
        node* c = p->child;
        if(c) {
            do {
                q.push(c);
                c = c->right;
            } while (c != p->child);
        }
        node* temp = p;
        p = p->right;
        delete temp;
    }while(p != heapRoot);

    while(!q.empty()){
        node* next = q.front();
        q.pop();

        node* c = next->child;
        if(c) {
            do {
                q.push(c);
                c = c->right;
            } while (c != next->child);
        }
        delete next;
    }
    heapRoot = nullptr;
    nodeCount = 0;
}

