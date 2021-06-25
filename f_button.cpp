#include "f_button.h"

MyButton::MyButton() {
}

MyButton::MyButton(int pin) {
    this->pin = pin;
    pinMode(pin, INPUT);
    state = false;
    lastReading = false;
    debounceDelay = 50;
    lastState = false;
}

bool MyButton::read() {
    int reading = digitalRead(pin);

    if (reading != lastReading) {
        waiter.wait(debounceDelay);
    }

    if (waiter.isExceeded() and reading != state) {
        state = reading;
    }

    lastReading = reading;

    return state;
}

bool MyButton::pressed(bool risingEdge) {
    read();

    if (state == lastState) return false;

    lastState = state;

    return (risingEdge and state) or (not risingEdge and not state);
}