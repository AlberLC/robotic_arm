#include "f_data_structures.h"

template <class T>
CircularArray<T>::CircularArray(int size) {
    this->size = this->max(0, size);
    index = size - 1;
    values = new T[size];
}

template <class T>
T& CircularArray<T>::operator[](int i) {
    i = (index + i) % size;
    if (i < 0) {
        i += size;
    }
    return values[i];
}

template <class T>
void CircularArray<T>::append(T value) {
    index = index + 1 % size;
    values[index] = value;
}

template <class T>
AverageCircularArray<T>::AverageCircularArray(int size, T initValue, int periods) : CircularArray<T>(size) {
    for (int i = 0; i < size; ++i) {
        (*this)[i] = initValue;
    }
    this->periods = this->constrain(periods, 0, size);
}

template <class T>
float AverageCircularArray<T>::getMultiplier() {
    return 2 / (periods + 1);
}

template <class T>
float AverageCircularArray<T>::getAverage(int i) {
    float sum;
    for (int j = i; j >= i - (periods - 1); --j) {
        sum += (*this)[j];
    }
    return sum / periods;
}

template <class T>
float AverageCircularArray<T>::getEMA(int i) {
    if (-i >= this->size - periods) {
        return getAverage(i);
    }

    float lastEma = getEMA(i - 1);
    return ((*this)[i] - lastEma) * getMultiplier() + lastEma;
}