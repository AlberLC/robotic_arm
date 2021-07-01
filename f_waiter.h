#pragma once

#include "f_time.h"

class Waiter {
   private:
    unsigned long waitingTime;
    unsigned long lastTime;

   public:
    Waiter();

    void wait(unsigned long waitingTime);
    bool isExceeded();
};