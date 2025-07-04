//
// Created by Jovan Zivanovic on 4.7.25..
//

#include "Sorter.h"
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
