#ifndef THEIL_SEN_H
#define THEIL_SEN_H

#include <stddef.h> // Potrzebne dla typu size_t

// Struktura przechowuj�ca wynik estymacji
typedef struct {
    float slope;    // Nachylenie
    float intercept; // Wyraz wolny
} TheilSenResult;

// Funkcja obliczaj�ca estymator Theil-Sen
TheilSenResult TheilSen_Estimate(const float* x, const float* y, size_t length);

#endif // THEIL_SEN_H