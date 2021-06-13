#pragma once

class Waiter {
   private:
    unsigned long goalTime;

   public:
    Waiter() {
        goalTime = 0;
    }

    void waitUntil(unsigned long goalTime) {
        this->goalTime = goalTime;
    }

    bool isExceeded(unsigned long currentTime) {
        return currentTime >= goalTime;
    }
};
