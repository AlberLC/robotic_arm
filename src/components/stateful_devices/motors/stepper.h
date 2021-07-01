#pragma once

#include "../../../globals/config.h"
#include "../../potentiometer.h"
#include "Adafruit_MotorShield.h"

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
