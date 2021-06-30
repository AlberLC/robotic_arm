#pragma once

#include "f_config.h"
#include "f_potentiometer.h"

class Stepper {
   protected:
    int pin;
    int minPos;
    int maxPos;
    Potentiometer potentiometer;

   public:
    Stepper() = default;
    Stepper(int pin, int minPos, int maxPos);

    int getMinPos();
    int getMaxPos();
    int getCurrentPos();
};