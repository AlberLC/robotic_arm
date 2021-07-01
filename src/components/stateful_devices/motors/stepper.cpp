#include "stepper.h"

Stepper::Stepper(int pin, int minPos, int maxPos) {
    this->pin = pin;
    this->minPos = minPos;
    this->maxPos = maxPos;
    potentiometer = Potentiometer(POTENTIOMETER_PIN, POTENTIOMETER_MIN_READ, POTENTIOMETER_MAX_READ);
}

int Stepper::getMinPos() {
    return minPos;
}

int Stepper::getMaxPos() {
    return maxPos;
}

int Stepper::getCurrentPos() {
    return map(potentiometer.read(), potentiometer.getMinLimit(), potentiometer.getMaxLimit(), getMinPos(), getMaxPos());
}