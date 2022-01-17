#pragma once

#include <arduino.h>

#include "../utils/data_structures.h"
#include "component.h"

class Potentiometer : Component {
   protected:
    int minLimit;
    int maxLimit;
    AverageCircularArray<int> values;

   public:
    using Component::Component;
    Potentiometer(int pin, int minLimit, int maxLimit);

    int getMinLimit();
    int getMaxLimit();
    int rawRead();
    int read();
};
