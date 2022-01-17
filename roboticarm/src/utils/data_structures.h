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
    CircularArray(int size) {
        this->size = max(0, size);
        index = size - 1;
        values = new T[size];
    }

    T& operator[](int i) {
        return values[mod(index + i, size)];
    }

    void append(T value) {
        index = index + 1 % size;
        values[index] = value;
    }
};

template <class T>
class AverageCircularArray : public CircularArray<T> {
   public:
    int periods;

    using CircularArray<T>::CircularArray;
    AverageCircularArray(int size, T initValue, int periods = EMA_PERIODS) : CircularArray<T>(size) {
        for (int i = 0; i < size; ++i) {
            (*this)[i] = initValue;
        }
        this->periods = constrain(periods, 0, size);
    }

    float getMultiplier() {
        return 2 / (periods + 1);
    }

    float getAverage(int i = 0) {
        float sum;
        for (int j = i; j >= i - (periods - 1); --j) {
            sum += (*this)[j];
        }
        return sum / periods;
    }

    float getEMA(int i = 0) {
        if (-i >= this->size - periods) {
            return getAverage(i);
        }

        float lastEma = getEMA(i - 1);
        return ((*this)[i] - lastEma) * getMultiplier() + lastEma;
    }
};