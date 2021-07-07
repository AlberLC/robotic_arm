#pragma once

#include <arduino.h>

#include "../globals/config.h"
#include "math.h"

template <class T>
class CircularArray {
   public:
    int size;
    int index;
    T* values;

    CircularArray() = default;
    CircularArray(int size);
    T& operator[](int i);
    void append(T value);
};

template <class T>
class AverageCircularArray : public CircularArray<T> {
   public:
    int periods;

    using CircularArray<T>::CircularArray;
    AverageCircularArray(int size, T initValue, int periods = EMA_PERIODS);
    float getMultiplier();
    float getAverage(int i = 0);
    float getEMA(int i = 0);
};