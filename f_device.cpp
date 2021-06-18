#pragma once

#include "f_waiter.cpp"

class Device {
   protected:
    enum class State { Done,
                       Waiting,
                       Paused,
                       Working };
    Waiter waiter;
    State state;

    Device() {
        state = State::Done;
    }

    void _loop() {
    }

   public:
    void loop(unsigned long currentTime, int retard = 0) {
        if (isDone() or isPaused() or not waiter.isExceeded(currentTime)) return;

        if (state != State::Working) {
            state = State::Working;
        }

        _loop();

        wait(retard, currentTime);
    }

    void moveToInitialPosition() {
    }

    void wait(unsigned long waitingTime, unsigned long currentTime) {
        state = State::Waiting;
        waiter.wait(waitingTime, currentTime);
    }

    bool isDone() {
        return state == State::Done;
    }

    bool isWaiting() {
        return state == State::Waiting;
    }

    bool isPaused() {
        return state == State::Paused;
    }

    bool isWorking() {
        return state == State::Working;
    }

    void play() {
        state = State::Waiting;
    }

    void pause() {
        state = State::Paused;
    }

    void stop() {
        moveToInitialPosition();
        pause();
    }
};