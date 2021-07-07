#include "math.h"

float lerp(float a, float b, float t) {
    return a + (b - a) * constrain(t, 0, 1);
}

template <class T>
T mod(T a, T b) {
    return a - (b * floor((float)a / b));
}

int sign(int n) {
    if (n > 0) return 1;
    if (n < 0) return -1;
    return 0;
}