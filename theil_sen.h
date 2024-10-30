#ifndef THEIL_SEN_H
#define THEIL_SEN_H

#include <stddef.h>

typedef struct {
    float slope;
    float intercept;
} TheilSenResult;

TheilSenResult TheilSen_Estimate(const float* x, const float* y, size_t length);

#endif // THEIL_SEN_H
