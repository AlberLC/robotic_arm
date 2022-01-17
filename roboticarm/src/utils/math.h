#pragma once

#include <arduino.h>
#include <math.h>

float lerp(float a, float b, float t);
int sign(int n);

template <class T>
T mod(T a, T b) {
    return a - (b * floor((float)a / b));
}
