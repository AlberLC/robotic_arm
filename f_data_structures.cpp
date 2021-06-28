#include "f_data_structures.h"

template <class T>
CircularArray<T>::CircularArray(int size) {
    this->size = size;
    index = size - 1;
    values = new T[size];
}

template <class T>
T& CircularArray<T>::operator[](int i) {
    i = index + i;
    if (i < 0) {
        i += (-i / size + 1) * size;
    }
    return values[i];
}

template <class T>
void CircularArray<T>::append(T value) {
    index = index + 1 % size;
    values[index] = value;
}

template <class T>
AverageCircularArray<T>::AverageCircularArray(int size, T initValue, int averageN) : CircularArray<T>(size) {
    for (int i = 0; i < size; ++i) {
        (*this)[i] = initValue;
    }
    this->averageN = this->max(0, averageN);
}

template <class T>
float AverageCircularArray<T>::getAverage() {
    float sum;
    for (int i = this->index; i >= this->index - (averageN - 1); i--) {
        sum += this->values[i];
    }
    return sum / averageN;
}