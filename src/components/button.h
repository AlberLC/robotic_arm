#pragma once

#include <arduino.h>

#include "../globals/config.h"
#include "../utils/waiter.h"

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
