#include <stdio.h>
#include "theil_sen.h"

int main() {
    float x[] = {1, 2, 3, 4, 5};
    float y[] = {2, 4, 5, 4, 5};
    size_t length = sizeof(x) / sizeof(x[0]);

    TheilSenResult result = TheilSen_Estimate(x, y, length);

    printf("Nachylenie: %f\n", result.slope);
    printf("Wyraz wolny: %f\n", result.intercept);

    return 0;
}