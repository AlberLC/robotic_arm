#pragma once

#include "../../utils/f_waiter.h"

class StatefulDevice {
   protected:
    enum class State { Done,
                       Waiting,
                       Paused,
                       Working };

    Waiter waiter;
    State state;

    StatefulDevice();

    bool initLoop();

   public:
    void wait(unsigned long waitingTime);
    bool isDone();
    bool isWaiting();
    bool isPaused();
    bool isWorking();
    void play();
    void pause();
};