#include "stepper.h"

Stepper::Stepper(int pin, int steps, int minPos, int maxPos, Potentiometer* potentiometer) : Stepper(pin, steps, UNDEFINED, minPos, maxPos, potentiometer) {
}

Stepper::Stepper(int pin, int steps, int initPos, int minPos, int maxPos, Potentiometer* potentiometer) : Motor(pin, initPos, minPos, maxPos) {
    this->steps = steps;
    this->potentiometer = potentiometer;

    if (this->potentiometer) {
        currentPos = potentiometer->read();
        roundedCurrentPos = currentPos;
    }
}

int Stepper::getCurrentPos() {
    return map(Motor::getCurrentPos(), potentiometer->getMinLimit(), potentiometer->getMaxLimit(), getMinPos(), getMaxPos());
}

int Stepper::getPotentiometerPos() {
    return potentiometer->read();
}

int Stepper::getSteps() {
    return steps;
}

Potentiometer* Stepper::getPotenciometer() {
    return potentiometer;
}

int Stepper::calculateAngularDistance(int startPos, int finalPos) {
    int angularDistanceUp = UNDEFINED;
    if (getMaxPos() != UNDEFINED) {
        if (startPos < finalPos < getMaxPos() or getMaxPos() < currentPos < finalPos) {
            angularDistanceUp = finalPos - startPos;
        } else if (finalPos < getMaxPos() < currentPos) {
            angularDistanceUp = mod(finalPos - startPos, 360);
        }
    }

    int angularDistanceDown = UNDEFINED;
    if (getMinPos() != UNDEFINED) {
        if (getMinPos() < finalPos < startPos or finalPos < currentPos < getMinPos()) {
            angularDistanceDown = finalPos - startPos;
        } else if (startPos < getMinPos() < finalPos) {
            angularDistanceDown = mod(finalPos - startPos, -360);
        }
    }

    if (angularDistanceUp != UNDEFINED) {
        if (angularDistanceDown != UNDEFINED and abs(angularDistanceDown) < abs(angularDistanceUp)) {
            return angularDistanceDown;
        }
        return angularDistanceUp;
    }
    if (angularDistanceDown != UNDEFINED) {
        return angularDistanceDown;
    }
    return UNDEFINED;
}

void Stepper::writeMotor(int pos) {
    //todo
}
