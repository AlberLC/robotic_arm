#pragma once

#include "../globals/f_config.h"
#include "../utils/f_waiter.h"
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
    MyButton() = default;
    MyButton(int pin);

    bool read();
    bool pressed(bool risingEdge = true);
};
