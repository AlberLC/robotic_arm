#pragma once

#include <arduino.h>

#include "../globals/config.h"
#include "../utils/data_structures.h"

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