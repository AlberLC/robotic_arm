#pragma once

#include "f_waiter.h"

class Device {
   protected:
    enum class State { Done,
                       Waiting,
                       Paused,
                       Working };
    Waiter waiter;
    State state;

    Device();

    bool initLoop();

   public:
    void moveToInitialPosition();
    void wait(unsigned long waitingTime);
    bool isDone();
    bool isWaiting();
    bool isPaused();
    bool isWorking();
    void play();
    void pause();
    void stop();
};