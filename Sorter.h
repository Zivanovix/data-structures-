//
// Created by Jovan Zivanovic on 4.7.25..
//

#ifndef DATA_STRUCTURES__SORTER_H
#define DATA_STRUCTURES__SORTER_H


class Sorter {
public:


    static void selectionSort(int* arr, int n); // Direct selection
    static void heapSort(int* arr, int n);

    static void bubbleSort(int* arr, int n); // Direct exchange
    static void quickSort(int* arr, int n);

    static void insertionSort(int* arr, int n); // Direct insertion
    static void shellSort(int* arr, int n);

    static void mergeSort(int* arr, int n); // Direct merging

    // Special linear complexity algorithms, non comparison-based sorts
    static void radixSort(int* arr, int n); // integers have to be non negative
    static void countingSort(int* arr, int n); // assume keys in range 0, 1000


protected:
    static int partition(int*arr, int low, int high);
    static void quickSort(int* arr, int low, int high);
    static void shellSort(int* arr, int n, int* h, int t);
    static void mergeSort(int* tab, int* temp, int low, int high);
    static void merge(int* a, int* b, int low, int m, int high);
    static void adjust(int* a, int i, int n);
};


#endif //DATA_STRUCTURES__SORTER_H
