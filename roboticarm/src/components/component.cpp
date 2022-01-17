#include "component.h"

Component::Component(int pin) {
    this->pin = pin;
}

int Component::getPin() {
    return pin;
}

void Component::setPin(int pin) {
    this->pin = pin;
}