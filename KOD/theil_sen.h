#ifndef THEIL_SEN_H
#define THEIL_SEN_H

#include <stddef.h> // Potrzebne dla typu size_t

// Struktura przechowująca wynik estymacji
typedef struct {
    float slope;    // Nachylenie
    float intercept; // Wyraz wolny
} TheilSenResult;

// Funkcja obliczająca estymator Theil-Sen
TheilSenResult TheilSen_Estimate(const float* x, const float* y, size_t length);

#endif // THEIL_SEN_H