#include "theil_sen.h"
#include "stdlib.h"
#include "stddef.h"

static int porownaj_floaty(const void* a, const void* b) {
    float roznica = (*(const float*)a - *(const float*)b);
    return (roznica > 0) - (roznica < 0);
}

static float mediana(float* tablica, size_t dlugosc) {
    qsort(tablica, dlugosc, sizeof(float), porownaj_floaty);
    if (dlugosc % 2 == 0) {
        return (tablica[dlugosc / 2 - 1] + tablica[dlugosc / 2]) / 2.0f;
    } else {
        return tablica[dlugosc / 2];
    }
}

WynikTheilSena TheilSen_Estymator(const float* x, const float* y, size_t dlugosc) {
    if (dlugosc < 2) {
        WynikTheilSena wynik_bledu = {0.0f, 0.0f};
        return wynik_bledu;
    }

    size_t liczba_par = (dlugosc * (dlugosc - 1)) / 2;

    float nachylenia[liczba_par];
    size_t indeks = 0;

    for (size_t i = 0; i < dlugosc - 1; i++) {
        for (size_t j = i + 1; j < dlugosc; j++) {
            if (x[j] != x[i]) {
                nachylenia[indeks++] = (y[j] - y[i]) / (x[j] - x[i]);
            }
        }
    }

    if (indeks == 0) {
        WynikTheilSena wynik_bledu = {0.0f, 0.0f};
        return wynik_bledu;
    }

    float mediana_nachylenia = mediana(nachylenia, indeks);

    float wyrazy_wolne[dlugosc];
    for (size_t i = 0; i < dlugosc; i++) {
        wyrazy_wolne[i] = y[i] - mediana_nachylenia * x[i];
    }

    float mediana_wyrazu_wolnego = mediana(wyrazy_wolne, dlugosc);

    WynikTheilSena wynik = {mediana_nachylenia, mediana_wyrazu_wolnego};
    return wynik;
}
