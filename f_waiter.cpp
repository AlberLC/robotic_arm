#pragma once

class Waiter {
   private:
    unsigned long waitingTime;
    unsigned long lastTime;

   public:
    Waiter() {
        waitingTime = 0;
        lastTime = 0;
    }

    void wait(unsigned long waitingTime, unsigned long currentTime) {
        this->waitingTime = waitingTime;
        lastTime = currentTime;
    }

    bool isExceeded(unsigned long currentTime) {
        return currentTime - lastTime >= waitingTime;
    }
};
