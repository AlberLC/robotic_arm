#pragma once

#include "arduino.h"
#include "f_data_structures.h"

class Potentiometer {
   protected:
    int pin;
    AverageCircularArray<int> values;

   public:
    Potentiometer() = default;
    Potentiometer(int pin);
    int rawRead();
    int read();
};
