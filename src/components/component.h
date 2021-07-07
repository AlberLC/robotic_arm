#pragma once

#include <arduino.h>

#include "../globals/config.h"

class Component {
   protected:
    int pin;

   public:
    Component() = default;
    Component(int pin);

    int getPin();
    void setPin(int pin);
};