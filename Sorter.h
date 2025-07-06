//
// Created by Jovan Zivanovic on 4.7.25..
//

#ifndef DATA_STRUCTURES__SORTER_H
#define DATA_STRUCTURES__SORTER_H


class Sorter {
public:
    static void radixSort(int* arr, int n);

    static void selectionSort(int* arr, int n); // Direct selection


    static void bubbleSort(int* arr, int n); // Direct exchange
    static void quickSort(int* arr, int n);

    static void insertionSort(int* arr, int n); // Direct insertion
    static void shellSort(int* arr, int n);

protected:
    static int partition(int*arr, int low, int high);
    static void quickSort(int* arr, int low, int high);
    static void shellSort(int* arr, int n, int* h, int t);
};


#endif //DATA_STRUCTURES__SORTER_H
