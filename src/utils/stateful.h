#pragma once

#include "waiter.h"

class Stateful {
   protected:
    enum class State { Done,
                       Waiting,
                       Paused,
                       Working };

    Waiter waiter;
    State state;

    Stateful();

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