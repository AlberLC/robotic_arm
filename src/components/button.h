#pragma once

#include <arduino.h>

#include "../globals/config.h"
#include "../utils/waiter.h"
#include "component.h"

class MyButton : Component {
   private:
    bool state;
    bool lastReading;
    unsigned debounceDelay;
    Waiter waiter;
    bool lastState;

   public:
    using Component::Component;
    MyButton(int pin);

    bool read();
    bool pressed(bool risingEdge = true);
};
