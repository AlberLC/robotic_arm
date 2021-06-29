#include "f_potentiometer.h"

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
    values = AverageCircularArray<int>(10, 0);
}

int Potentiometer::rawRead() {
    return analogRead(pin);
}

int Potentiometer::read() {
    values.append(rawRead());
    return values.getAverage();
}