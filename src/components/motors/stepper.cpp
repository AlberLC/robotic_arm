#include "stepper.h"

Stepper::Stepper(int pin, int initPos, int minPos, int maxPos) : Motor(pin, initPos, minPos, maxPos) {
    potentiometer = Potentiometer(POTENTIOMETER_PIN, POTENTIOMETER_MIN_LIMIT, POTENTIOMETER_MAX_LIMIT);
}

int Stepper::getCurrentPos() {
    return map(potentiometer.read(), potentiometer.getMinLimit(), potentiometer.getMaxLimit(), getMinPos(), getMaxPos());
}

void Stepper::writeMotor() {
}
