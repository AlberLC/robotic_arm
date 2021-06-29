#pragma once

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
    int averageN;

    AverageCircularArray() = default;
    AverageCircularArray(int size, T initValue, int averageN = 10);
    float getAverage();
};
