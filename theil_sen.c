#include "theil_sen.h"
#include <stdlib.h>

static int compare_floats(const void* a, const void* b) {
    float diff = (*(const float*)a - *(const float*)b);
    return (diff > 0) - (diff < 0);
}

static float median(float* arr, size_t length) {
    qsort(arr, length, sizeof(float), compare_floats);
    if (length % 2 == 0) {
        return (arr[length / 2 - 1] + arr[length / 2]) / 2.0f;
    } else {
        return arr[length / 2];
    }
}

TheilSenResult TheilSen_Estimate(const float* x, const float* y, size_t length) {
    if (length < 2) {
        TheilSenResult error_result = {0.0f, 0.0f};
        return error_result;
    }

    size_t num_pairs = (length * (length - 1)) / 2;
    float* slopes = (float*)malloc(num_pairs * sizeof(float));
    if (slopes == NULL) {
        TheilSenResult error_result = {0.0f, 0.0f};
        return error_result;
    }

    size_t index = 0;
    for (size_t i = 0; i < length - 1; i++) {
        for (size_t j = i + 1; j < length; j++) {
            if (x[j] != x[i]) {
                slopes[index++] = (y[j] - y[i]) / (x[j] - x[i]);
            }
        }
    }

    if (index == 0) {
        free(slopes);
        TheilSenResult error_result = {0.0f, 0.0f};
        return error_result;
    }

    float slope_median = median(slopes, index);
    free(slopes);

    float* intercepts = (float*)malloc(length * sizeof(float));
    if (intercepts == NULL) {
        TheilSenResult error_result = {slope_median, 0.0f};
        return error_result;
    }

    for (size_t i = 0; i < length; i++) {
        intercepts[i] = y[i] - slope_median * x[i];
    }

    float intercept_median = median(intercepts, length);
    free(intercepts);

    TheilSenResult result = {slope_median, intercept_median};
    return result;
}

