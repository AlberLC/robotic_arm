#include "stateful.h"

Stateful::Stateful() {
    state = State::Done;
}

bool Stateful::initLoop() {
    if (isDone() or isPaused() or not waiter.isExceeded()) return false;

    if (state != State::Working) {
        state = State::Working;
    }

    return true;
}

void Stateful::wait(unsigned long waitingTime) {
    state = State::Waiting;
    waiter.wait(waitingTime);
}

bool Stateful::isDone() {
    return state == State::Done;
}

bool Stateful::isWaiting() {
    return state == State::Waiting;
}

bool Stateful::isPaused() {
    return state == State::Paused;
}

bool Stateful::isWorking() {
    return state == State::Working;
}

void Stateful::play() {
    state = State::Waiting;
}

void Stateful::pause() {
    state = State::Paused;
}