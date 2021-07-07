#pragma once

#include <arduino.h>
#include <math.h>

float lerp(float a, float b, float t);
// template <class T> todo innecesario?
// T _mod(T a, T b);
template <class T>
T mod(T a, T b);
int sign(int n);