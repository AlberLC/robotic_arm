#include "f_waiter.h"

#include "f_time.h"

Waiter::Waiter() {
    waitingTime = 0;
    lastTime = 0;
}

void Waiter::wait(unsigned long waitingTime) {
    this->waitingTime = waitingTime;
    lastTime = currentTime;
}

bool Waiter::isExceeded() {
    return currentTime - lastTime >= waitingTime;
}
