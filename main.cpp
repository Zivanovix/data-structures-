#include <iostream>
#include "Sorter.h"
#include "Heap.h"
#include "PriorityQueue.h"
#include <string>


void printArr(int* arr, int n){
    for(int i=0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}
int testSort( void (*func)(int* a, int size), int* arr, int n, int asc = 1){
    func(arr, n);
    for (int i=0; i < n-1; i++) {
        int ascPair = asc && arr[i] <= arr[i + 1];
        int descPair = !asc && arr[i] >= arr[i + 1];
        if (!ascPair && !descPair) {
            std::cout << "The sort function provided doesn't work correctly!\n";
            return 0;
        }
    }
    printArr(arr, n);
    return 1;
}

int insertArr(int* arr){
    int n;
    std::cout << "Enter the size of the array!" << std::endl;
    std::cin >> n;
    std::cout << "Enter the array's elements!" << std::endl;

    for (int i=0; i < n; i++)
        std::cin >> arr[i];
    return n;
}


void insertArrAndSort(void (*sort)(int* arr, int n), int* arr){
    int n  = insertArr(arr);
    testSort(sort, arr, n);
}
const unsigned MAX_LEN = 1000;
int a[MAX_LEN];

int main() {
    /*
    insertArrAndSort(Sorter::radixSort, a);
    insertArrAndSort(Sorter::selectionSort, a);
    insertArrAndSort(Sorter::bubbleSort, a);
    insertArrAndSort(Sorter::insertionSort, a);
    insertArrAndSort(Sorter::quickSort, a);
    insertArrAndSort(Sorter::shellSort, a);

    insertArrAndSort(Sorter::mergeSort, a);
    insertArrAndSort(Sorter::countingSort, a);
    insertArrAndSort(Sorter::heapSort, a);

     */


    /*
    Heap h(20);
    for(int i = 0; i < 20; i++) h.insert(i & 7);
    std::cout << h << std::endl;

    int niz[]{5,2,7,4,9,11,4,2,1,5,9,13,44,21,0};
    Heap::sort(niz, sizeof(niz) / sizeof(int));
    for(int i : niz) std::cout << i << " ";
    std::cout << std::endl;

    PriorityQueue pq(4);
    try{
        pq.insert(5).insert(7).insert(1);
        std::cout << pq.remove() << " ";
        pq.insert(0).insert(3).insert(2);
        while(!pq.isEmpty())
            std::cout << pq.remove() << " ";

        std::cout << std::endl;
    }
    catch (char const* s){
        std::cout << std:: endl << s << std::endl;
    }
    /*
    return 0;
}
// 10 9 8 7 6 3 4 2 1 5
// -1 -2 -3 -4 5 11 1
// -1 3 -2