#pragma once

#include "f_waiter.cpp"
#include "arduino.h"

class MyButton {
   private:
    int pin;
    bool state;
    bool lastReading;
    unsigned debounceDelay;
    Waiter waiter;
    bool lastState;

   public:
    MyButton() {
    }

    MyButton(int pin) {
        this->pin = pin;
        pinMode(pin, INPUT);
        state = false;
        lastReading = false;
        debounceDelay = 50;
        lastState = false;
    }

    bool read(unsigned long currentTime) {
        int reading = digitalRead(pin);

        if (reading != lastReading) {
            waiter.wait(debounceDelay, currentTime);
        }

        if (waiter.isExceeded(currentTime)) {
            if (reading != state) {
                state = reading;
            }
        }

        lastReading = reading;

        return state;
    }

    bool pressed(unsigned long currentTime, bool risingEdge = true) {
        int state = read(currentTime);

        if (lastState == state) return false;

        lastState = state;

        return (risingEdge and state) or (not risingEdge and not state);
    }
};
