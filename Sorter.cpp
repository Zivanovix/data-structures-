//
// Created by Jovan Zivanovic on 4.7.25..
//

#include "Sorter.h"
#include <cmath>

#define BITS_IN_BYTE 8


void Sorter::radixSort(int *arr, int n) {
    int *temp, *t, *count, *pref;
    int r, b, groups, mask, shift, count_n, i, j;

    // Broj bitova u grupi za procesiranje
    // Na osnovu 4 bita kljuceve razvrstavamo u 2^4 = 16 klasa
    r = 4;

    // Duzina int-a u bitovima
    b = sizeof(int) * BITS_IN_BYTE;

    // Inicijalizacija pomocnog niza za preuredjivanje

    temp = new int[n];

    // 2^r razlicitih varijanti, ako jedan radix ima r bita
    // count - brojacki niz
    // pre f- za prefiksnu sumu
    count_n = 1 << r;  // 10000
    count = new int[count_n];
    pref = new int[count_n];

    // Maska ima r jedinica
    mask = (1 << r)-1; // 1111

    // Broj grupa, u jednoj iteraciji sortiramo po jednoj grupi od 4 bita
    // Idemo od bitova manje tezine ka bitovima vece tezine (<-)
    groups = b / r;

     // Algoritam
     for(i = 0, shift=0; i < groups; i++, shift+=r) {
         // Resetovanje niza za brojanje
         for(j=0; j < count_n; j++)
             count[j] = 0;

         // Brojanje elemenata
         for(j=0; j < n; j++) {
             // value of j-th group of r bits
             // j = 0  arr[j] = 0...0101, jNibbleVal = 5
             // j = 1  arr[j] = 0...0111 0101, jNibbleVal = 7
             auto jNibbleVal = (arr[j] >> shift) & mask;
             count[jNibbleVal]++;
         }
         // Racunanje prefiksnih suma
         // pref[i] kaze koliko ima elemenata u a[j] sa radix-om (odgovarajuca nibla)
         // koji je maxi od mog
         pref[0] = 0;
         for(j = 1; j < count_n; j++){
             pref[j] = pref[j-1] + count[j-1];
         }
         // Pomeranje elemenata odgovarajuce grupe na svoje mesto
         for(j=0; j < n; j++) {
             auto jNibbleVal = (arr[j] >> shift) & mask;
             temp[pref[jNibbleVal]++] = arr[j];
         }

         // Zameni pokazivace na nizove

         t = arr;
         arr = temp;
         temp = t;

         // Obrati paznju da arr svaku iteraciju menja niz na koji pokazuje
         // Mi smo predali niz koji treba sortirati po referenci i arr inicijalizovali da pokazuje na njega
         // Nakon svake neparne iteracije arr pokazuje na drugi niz, koji sadrzi progresiju napravljenu do tog trenutka
         // Iteracija ima onoliko koliko ima grupa, a grupa je 4 bita u ovom primer
         // Zbog toga sto brojevi imaju 32 bita, a 32/4 = 8 iteracija, sto je paran broj
         // arr ce pokazivati na pocetni niz gde ce vrednosti biti sortirane, pa sve lepo radi
         // Kada bi brojevi bili vrednosti od 4 bita i sve se radilo u jednoj iteraciji, sortirani niz bi se nalazio u temp
         // Sto korisnik ne bi mogao da vidi jer niz koji je on prosledio nije nikako promenjen, za npr 12bita niz bi bio promenjen
         // Ali bi izlaz za korisnika bio iznenadjujuc jer se tu nalazi pretposlednji korak u sortiranju, a poslednji je ostao u temp

     }
    delete[] temp;
    delete[] count;
    delete[] pref;
}

void Sorter::selectionSort(int *arr, int n) {
    int pos, temp; // position of the minimum from unsorted part
    for(int i=0; i < n-1; i++){
        pos = i;
        for(int j=i+1; j < n; j++) {
            if(arr[j] < arr[pos])
                pos = j;
        }
        temp = arr[pos];
        arr[pos] = arr[i];
        arr[i] = temp;
    }
}

void Sorter::bubbleSort(int* arr, int n) {
    int bound, temp; // bound of the unsorted part
    int pos = n-1; // position where the last swap happened
    for(int i=0; i < n-1; i++){
       bound = pos;
       for(int j=0; j < bound; j++){
           if(arr[j] > arr[j+1]){
               temp = arr[j];
               arr[j] = arr[j+1];
               arr[j+1] = temp;
               pos = j;
           }
       }
    }
}

void Sorter::insertionSort(int* arr, int n) {
    int curr, j;
    for(int i=1; i < n; i++) {
        curr = arr[i];
        j = i - 1;
        while(j >= 0 && curr < arr[j]){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = curr;
    }
}

void Sorter::quickSort(int *arr, int low, int high) {
    if(low >= high-1)
        return;

    int j = partition(arr, low, high);
    quickSort(arr, low, j);
    quickSort(arr, j+1, high);

}

int Sorter::partition(int *arr, int low, int high) {
    int i = low, j = high-1, pivot = arr[low], temp;

    while(i < j) {
        while (arr[i] <= pivot && i < j)
            i++;
        while (arr[j] > pivot)
            j--;
        if(i < j){
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[j];
    arr[j] = pivot;
    arr[low] = temp;
    return j;
}

void Sorter::quickSort(int *arr, int n) {
    quickSort(arr, 0, n);
}

void Sorter::shellSort(int *arr, int n) {
    int h[50];
    int k = 1;
    while (true) {
        h[k] = ((int)std::pow(3, k)-1) / 2;
        if(h[k] > n / 2) break;
        k++;
    }
    shellSort(arr, n, h, k);
}

void Sorter::shellSort(int *arr, int n, int *h, int t) {
    for(int i = t; i > 0; i--){
        int inc = h[i];

        for(int j = inc; j < n; j++){
            int y = arr[j];
            int k = j - inc;
            while(k >= 0 && y < arr[k]){
                arr[k+inc] = arr[k];
                k -= inc;
            }
            arr[k+inc] = y;
        }

    }
}
void Sorter::mergeSort(int* arr, int n){
    int* temp = new int[n/2+1];
    mergeSort(arr, temp, 0, n-1);
    delete[] temp;
}
void Sorter::mergeSort(int *arr, int *temp, int low, int high) {
    if(low >= high) return; // sequence of length one is sorted

    int m = (low + high) / 2;

    mergeSort(arr, temp, low, m);
    mergeSort(arr, temp, m+1, high);

    merge(arr, temp, low, m, high);
}

void Sorter::merge(int *a, int *temp, int low, int m, int high) {
    int i = 0, j = low, k;

    // temp = a[low, mid]
    while(j <= m)
        temp[i++] = a[j++];

    i = 0;
    k = low;

    // merge temp[] and a[mid+1, high] into a[low, high]
    // while one of the halfs is not fully copied
    while(k < j && j <= high) {
        if(temp[i] <= a[j])
            a[k++] = temp[i++];
        else
            a[k++] = a[j++];
    }
    // if the temp is fully copied, then we dont have to do anything
    // because remaining part of second array is already in a
    // if j = high and temp isn't fully copied, we have to copy the remaining elements
    while(k < j) {
        a[k++] = temp[i++];
    }
}

void Sorter::countingSort(int *arr, int n) {
    const int MAX_NUM = 1000;
    const int MIN_NUM = 0;
    const int RANGE_LEN = MAX_NUM - MIN_NUM + 1;
    int* count = new int[RANGE_LEN];

    // init counter for each element to 0
    for(int i=0; i < RANGE_LEN; count[i++] = 0);

    // count the occurrences of each element
    for(int i=0; i < n; i++) count[arr[i]]++;

    // transform counter array to such that count[i] shows
    // how many elements are smaller or equal then i in arr (prefix sum)
    // so now we read index of a[i] in sorted arr in count[a[i]]--,
    for(int i=1; i < RANGE_LEN; i++) count[i] += count[i-1];

    // reconstruct the array

    for(int i=n-1; i <= 0; i--) arr[count[arr[i]]--] = arr[i];

    delete[] count;
}

void Sorter::adjust(int* a, int i, int n) {
    int k = a[i];
    int j = 2*i + 1;
    while(j < n){
        if(j + 1 < n && a[j] < a[j+1])
            j = j + 1;
        if(k >= a[j]) {
            a[(j-1)/2] = k;
            return;
        }
        else {
            a[(j-1)/2] = a[j];
            j = 2*j + 1;
        }
    }
    a[(j-1)/2] = k;
}

void Sorter::heapSort(int *arr, int n) {
    //create heap;
    for(int i = (n-2)/2; i >= 0; i--)
        adjust(arr, i, n);
    for(int i=n-1; i >= 1; i--){
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        adjust(arr, 0, i);
    }
}
