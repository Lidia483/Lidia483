#ifndef THEIL_SEN_H
#define THEIL_SEN_H

#include <stddef.h> // Potrzebne dla typu size_t

// Struktura przechowująca wynik estymacji
typedef struct {
    float nachylenie;    // Nachylenie
    float wyraz_wolny;   // Wyraz wolny
} WynikTheilSena;

// Funkcja obliczająca estymator Theil-Sen
WynikTheilSena TheilSen_Estymator(const float* x, const float* y, size_t dlugosc, uint32_t *rzad);

#endif // THEIL_SEN_H
