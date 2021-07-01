#pragma once

#include "../../../globals/f_config.h"
#include "../../f_potentiometer.h"
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
