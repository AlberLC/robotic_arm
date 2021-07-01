#pragma once

#include "../globals/f_config.h"
#include "../utils/f_data_structures.h"
#include "arduino.h"

class Potentiometer {
   protected:
    int pin;
    int minLimit;
    int maxLimit;
    AverageCircularArray<int> values;

   public:
    Potentiometer() = default;
    Potentiometer(int pin, int minRead, int maxRead);

    int getMinLimit();
    int getMaxLimit();
    int rawRead();
    int read();
};
