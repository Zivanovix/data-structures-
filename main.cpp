#include <iostream>
#include "Sorter.h"



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
    insertArrAndSort(Sorter::radixSort, a);
    insertArrAndSort(Sorter::selectionSort, a);
    insertArrAndSort(Sorter::bubbleSort, a);
    insertArrAndSort(Sorter::insertionSort, a);
    insertArrAndSort(Sorter::quickSort, a);
    insertArrAndSort(Sorter::shellSort, a);

    return 0;
}
// 10 9 8 7 6 3 4 2 1 5
// -1 -2 -3 -4 5 11 1
// -1 3 -2