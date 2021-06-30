#pragma once

#include "arduino.h"
#include "f_config.h"
#include "f_waiter.h"

class MyButton {
   private:
    int pin;
    bool state;
    bool lastReading;
    unsigned debounceDelay;
    Waiter waiter;
    bool lastState;

   public:
    MyButton() = default;
    MyButton(int pin);

    bool read();
    bool pressed(bool risingEdge = true);
};
