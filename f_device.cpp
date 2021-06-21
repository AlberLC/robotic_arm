#include "f_device.h"

Device::Device() {
    state = State::Done;
}

bool Device::initLoop() {
    if (isDone() or isPaused() or not waiter.isExceeded()) return false;

    if (state != State::Working) {
        state = State::Working;
    }

    return true;
}

void Device::moveToInitialPosition() {
}

void Device::wait(unsigned long waitingTime) {
    state = State::Waiting;
    waiter.wait(waitingTime);
}

bool Device::isDone() {
    return state == State::Done;
}

bool Device::isWaiting() {
    return state == State::Waiting;
}

bool Device::isPaused() {
    return state == State::Paused;
}

bool Device::isWorking() {
    return state == State::Working;
}

void Device::play() {
    state = State::Waiting;
}

void Device::pause() {
    state = State::Paused;
}

void Device::stop() {
    moveToInitialPosition();
    pause();
}
