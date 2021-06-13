#pragma once

#include "f_waiter.cpp"

class Device {
   protected:
    enum class State { Done,
                       Waiting,
                       Paused,
                       Working };
    State stateBeforePaused = State::Done;
    Waiter waiter;
    State state;

    Device() {
        stateBeforePaused = State::Done;
    }

    void _loop() {
    }

   public:
    void loop(unsigned long currentTime, int retard = 0) {
        if (isDone() or isPaused() or not waiter.isExceeded(currentTime)) return;
        _loop();
        waitUntil(currentTime + retard);
    }

    void moveToInitialPosition(){        
    }

    void waitUntil(unsigned long goalTime) {
        waiter.waitUntil(goalTime);
        state = State::Waiting;
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
        state = stateBeforePaused;
    }

    void pause() {
        stateBeforePaused = state;
        state = State::Paused;
    }

    void stop(){
        moveToInitialPosition();
        pause();
    }
};