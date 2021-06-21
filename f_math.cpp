#include "f_math.h"

float lerp(float a, float b, float t) {
    return a + (b - a) * constrain(t, 0, 1);
}