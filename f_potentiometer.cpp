#include "f_potentiometer.h"

#include "f_config.h"

Potentiometer::Potentiometer(int pin) {
    this->pin = pin;
    values = AverageCircularArray<int>(AVERAGE_ARRAY_SIZE, 0);
}

int Potentiometer::rawRead() {
    return analogRead(pin);
}

int Potentiometer::read() {
    values.append(rawRead());
    return round(values.getEMA());
}