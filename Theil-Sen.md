#include <stdio.h>  // Biblioteka standardowa do operacji wejścia/wyjścia
#include <stdlib.h>  // Biblioteka standardowa do operacji związanych z alokacją pamięci

#define MAX_POINTS 100  // Maksymalna liczba punktów danych

// Deklaracje funkcji
float theil_sen_estimator(float x[], float y[], int n);  // Funkcja obliczająca estymator Theil-Sen
float compute_slope(float x1, float y1, float x2, float y2);  // Funkcja obliczająca nachylenie między dwoma punktami
float median(float arr[], int n);  // Funkcja obliczająca medianę tablicy
void quicksort(float arr[], int left, int right);  // Funkcja sortująca tablicę metodą QuickSort
int partition(float arr[], int left, int right);  // Funkcja dzieląca tablicę na części dla QuickSort
void swap(float *a, float *b);  // Funkcja zamieniająca dwie wartości typu float

int main(void) {
    // Przykładowe dane (wypełnij swoimi danymi)
    float x_data[MAX_POINTS] = {1, 2, 3, 4, 5};  // Przykładowe wartości x
    float y_data[MAX_POINTS] = {2, 4, 5, 4, 5};  // Przykładowe wartości y
    int n = 5; // Liczba punktów danych

    // Sprawdzenie, czy liczba punktów jest prawidłowa
    if (n <= 0 || n > MAX_POINTS) {
        printf("Invalid number of data points.\n");  // Wyświetlenie komunikatu o błędzie
        return -1;  // Zwrócenie błędu
    }

    // Oblicz nachylenie za pomocą estymatora Theil-Sen
    float slope = theil_sen_estimator(x_data, y_data, n);
    
    // Wydrukuj wynik
    printf("Theil-Sen Slope: %f\n", slope);  // Wyświetlenie obliczonego nachylenia

    return 0;  // Zakończenie programu
}

// Funkcja obliczająca estymator Theil-Sen
float theil_sen_estimator(float x[], float y[], int n) {
    int k = 0;  // Licznik liczby obliczonych nachyleń
    float slopes[MAX_POINTS * (MAX_POINTS - 1) / 2];  // Tablica do przechowywania nachyleń wszystkich par punktów

    // Obliczanie nachyleń dla wszystkich par punktów
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (x[i] != x[j]) {  // Unikaj dzielenia przez zero
                slopes[k++] = compute_slope(x[i], y[i], x[j], y[j]);  // Obliczanie nachylenia i dodanie do tablicy
            }
        }
    }

    // Obliczenie mediany nachyleń
    float slope_median = median(slopes, k);  // Obliczenie mediany nachyleń
    return slope_median;  // Zwrócenie mediany jako wynik
}

// Funkcja obliczająca nachylenie między dwoma punktami
float compute_slope(float x1, float y1, float x2, float y2) {
    return (y2 - y1) / (x2 - x1);  // Zwrócenie obliczonego nachylenia
}

// Funkcja obliczająca medianę tablicy
float median(float arr[], int n) {
    quicksort(arr, 0, n - 1);  // Sortowanie tablicy za pomocą QuickSort
    if (n % 2 == 0) {  // Jeśli liczba elementów jest parzysta
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;  // Zwrócenie średniej dwóch środkowych elementów
    } else {  // Jeśli liczba elementów jest nieparzysta
        return arr[n / 2];  // Zwrócenie środkowego elementu
    }
}

// Funkcja sortująca tablicę metodą QuickSort
void quicksort(float arr[], int left, int right) {
    if (left < right) {  // Jeśli podtablica ma więcej niż jeden element
        int pivot_index = partition(arr, left, right);  // Podzielenie tablicy na części
        quicksort(arr, left, pivot_index - 1);  // Rekurencyjne sortowanie lewej części
        quicksort(arr, pivot_index + 1, right);  // Rekurencyjne sortowanie prawej części
    }
}

// Funkcja dzieląca tablicę na części dla QuickSort
int partition(float arr[], int left, int right) {
    float pivot = arr[right];  // Wybór elementu pivot
    int i = left - 1;  // Inicjalizacja indeksu i
    for (int j = left; j < right; j++) {  // Iteracja po elementach tablicy
        if (arr[j] < pivot) {  // Jeśli element jest mniejszy niż pivot
            i++;  // Zwiększenie indeksu i
            swap(&arr[i], &arr[j]);  // Zamiana elementów
        }
    }
    swap(&arr[i + 1], &arr[right]);  // Zamiana pivota na odpowiednie miejsce
    return i + 1;  // Zwrócenie indeksu pivota
}

// Funkcja zamieniająca dwie wartości typu float
void swap(float *a, float *b) {
    float temp = *a;  // Tymczasowe przechowanie wartości a
    *a = *b;  // Przypisanie wartości b do a
    *b = temp;  // Przypisanie wartości temp do b
}

