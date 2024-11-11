#include <stdio.h>
#include "theil_sen.h"

int main() {
    float x[] = {2, 5, 10, 15, 20};
    float y[] = { 0.4, 0.8, 1, 2, 3};
    size_t length = sizeof(x) / sizeof(x[0]);

    TheilSenResult result = TheilSen_Estimate(x, y, length);

    printf("Nachylenie: %f\n", result.slope);
    printf("Wyraz wolny: %f\n", result.intercept);

    return 0;
}
 //Nachylenie: 0.138889
//Wyraz wolny: 0.105556
