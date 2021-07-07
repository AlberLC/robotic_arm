#include "stepper.h"

Stepper::Stepper(int pin, int initPos, int minPos, int maxPos) : Motor(pin, initPos, minPos, maxPos) {
    potentiometer = Potentiometer(POTENTIOMETER_PIN, POTENTIOMETER_MIN_LIMIT, POTENTIOMETER_MAX_LIMIT);
}

int Stepper::getCurrentPos() {
    return map(potentiometer.read(), potentiometer.getMinLimit(), potentiometer.getMaxLimit(), getMinPos(), getMaxPos());
}

int Stepper::calculateDistance(int startPos, int finalPos) {
    int angularDistanceUp;
    if (startPos < finalPos < getMaxPos() or getMaxPos() < currentPos < finalPos) {
        angularDistanceUp = finalPos - startPos;
    } else if (finalPos < getMaxPos() < currentPos) {
        angularDistanceUp = mod(finalPos - startPos, 360);
    }

    int angularDistanceDown;
    if (getMinPos() < finalPos < startPos or finalPos < currentPos < getMinPos()) {
        angularDistanceDown = finalPos - startPos;
    } else if (startPos < getMinPos() < finalPos) {
        angularDistanceDown = mod(finalPos - startPos, -360);
    }

    if (abs(angularDistanceUp) <= abs(angularDistanceDown)) {
        return angularDistanceUp;
    } else {
        return angularDistanceDown;
    }
}

void Stepper::writeMotor(int pos) {
    //todo
}
