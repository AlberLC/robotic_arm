#include "stateful_device.h"

StatefulDevice::StatefulDevice() {
    state = State::Done;
}

bool StatefulDevice::initLoop() {
    if (isDone() or isPaused() or not waiter.isExceeded()) return false;

    if (state != State::Working) {
        state = State::Working;
    }

    return true;
}

void StatefulDevice::wait(unsigned long waitingTime) {
    state = State::Waiting;
    waiter.wait(waitingTime);
}

bool StatefulDevice::isDone() {
    return state == State::Done;
}

bool StatefulDevice::isWaiting() {
    return state == State::Waiting;
}

bool StatefulDevice::isPaused() {
    return state == State::Paused;
}

bool StatefulDevice::isWorking() {
    return state == State::Working;
}

void StatefulDevice::play() {
    state = State::Waiting;
}

void StatefulDevice::pause() {
    state = State::Paused;
}