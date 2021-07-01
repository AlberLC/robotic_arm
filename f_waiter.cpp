#include "f_waiter.h"

Waiter::Waiter() {
    waitingTime = 0;
    lastTime = 0;
}

void Waiter::wait(unsigned long waitingTime) {
    this->waitingTime = waitingTime;
    lastTime = Time::currentTime;
}

bool Waiter::isExceeded() {
    return Time::currentTime - lastTime >= waitingTime;
}
