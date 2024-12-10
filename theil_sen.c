#include "theil_sen.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"

#define MAX_ELEMENTOW 2048

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


	WynikTheilSena TheilSen_Estymator(const float* x, const float* y, size_t dlugosc, uint32_t* rzad) {
		if (dlugosc < 2) {
			WynikTheilSena wynik_bledu = {0.0f, 0.0f};
			return wynik_bledu;
		}

		float nachylenia[MAX_ELEMENTOW];
		float wyrazy_wolne[MAX_ELEMENTOW];
		size_t indeks_nachylen = 0;
		size_t indeks_wyrazow = 0;


		for (size_t i = 0; i < dlugosc - 1; i++) {
			for (size_t j = i + 1; j < dlugosc; j++) {
				if (x[j][rzad] != x[i][rzad]) {
					if (indeks_nachylen < MAX_ELEMENTOW) {
						nachylenia[indeks_nachylen++] = (y[j][rzad] - y[i][rzad]) / (x[j][rzad] - x[i][rzad]);
					} else {
						break;
					}
				}
			}
			if (indeks_nachylen >= MAX_ELEMENTOW) break; // Przerwij główną pętlę
		}

		if (indeks_nachylen == 0) {
			WynikTheilSena wynik_bledu = {0.0f, 0.0f};
			return wynik_bledu;
		}

		float mediana_nachylenia = mediana(nachylenia, indeks_nachylen);


		for (size_t i = 0; i < dlugosc; i++) {
			if (indeks_wyrazow < MAX_ELEMENTOW) {
				wyrazy_wolne[indeks_wyrazow++] = y[i][rzad] - mediana_nachylenia * x[i][rzad];
			}
		}

		float mediana_wyrazu_wolnego = mediana(wyrazy_wolne, indeks_wyrazow);

		WynikTheilSena wynik = {mediana_nachylenia, mediana_wyrazu_wolnego};
		return wynik;
	}

