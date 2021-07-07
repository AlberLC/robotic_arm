#pragma once

#include <Adafruit_MotorShield.h>

#include "../potentiometer.h"
#include "motor.h"

class Stepper : public Motor {
   protected:
    Potentiometer potentiometer;

   public:
    using Motor::Motor;
    Stepper(int pin, int initPos, int minPos = -1, int maxPos = -1);

    int getCurrentPos();
    void writeMotor() override;
};
