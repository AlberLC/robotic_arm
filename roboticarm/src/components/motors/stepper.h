#pragma once

#include <Adafruit_MotorShield.h>

#include "../potentiometer.h"
#include "motor.h"

class Stepper : public Motor {
   protected:
    int steps;
    Potentiometer* potentiometer;

    int calculateAngularDistance(int startPos, int finalPos) override;

   public:
    using Motor::Motor;
    Stepper(int pin, int steps, int minPos = UNDEFINED, int maxPos = UNDEFINED, Potentiometer* Potentiometer = nullptr);
    Stepper(int pin, int steps, int initPos = UNDEFINED, int minPos = UNDEFINED, int maxPos = UNDEFINED, Potentiometer* Potentiometer = nullptr);

    int getCurrentPos();
    int getPotentiometerPos();
    int getSteps();
    Potentiometer* getPotenciometer();
    void writeMotor(int pos) override;
};
