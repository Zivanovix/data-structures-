#include <iostream>
#include "Sorter.h"

const unsigned MAX_LEN = 1000;
int a[MAX_LEN];
int main() {
    int n;
    std::cout << "Unesi duzinu niza!" << std::endl;
    std::cin >> n;
    std::cout << "Unesi elemente niza!" << std::endl;

    for(int i=0; i < n; i++)
        std::cin >> a[i];

    // works for unsigned integer keys
    Sorter::radixSort(a, n);

    for(int i=0; i < n; i++)
        std::cout << a[i] << " ";
    std::cout << std::endl;
    return 0;
}
