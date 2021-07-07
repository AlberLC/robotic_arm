#pragma once

#include <Adafruit_MotorShield.h>

#include "../potentiometer.h"
#include "motor.h"

class Stepper : public Motor {
   protected:
    Potentiometer potentiometer;

    int calculateAngularDistance(int startPos, int finalPos) override;

   public:
    using Motor::Motor;
    Stepper(int pin, int initPos, int minPos = -1, int maxPos = -1);

    int getCurrentPos();
    void writeMotor(int pos) override;
};
