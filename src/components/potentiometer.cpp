#include "potentiometer.h"

Potentiometer::Potentiometer(int pin, int minLimit, int maxLimit) {
    this->pin = pin;
    this->minLimit = minLimit;
    this->maxLimit = maxLimit;
    values = AverageCircularArray<int>(AVERAGE_ARRAY_SIZE, 0);
}

int Potentiometer::getMinLimit() {
    return minLimit;
}

int Potentiometer::getMaxLimit() {
    return maxLimit;
}

int Potentiometer::rawRead() {
    return analogRead(pin);
}

int Potentiometer::read() {
    values.append(rawRead());
    return round(values.getEMA());
}