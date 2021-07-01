#include "potentiometer.h"

Potentiometer::Potentiometer(int pin, int minRead, int maxRead) {
    this->pin = pin;
    this->minLimit = minRead;
    this->maxLimit = maxRead;
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