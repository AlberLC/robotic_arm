#pragma once

#include "f_waiter.cpp"
#include "Servo.h"

class MyServo {
   public:
    enum class State { Done,
                       Waiting,
                       Working };

    Servo *servo;
    Waiter waiter;
    State state;
    int finalPos;

    MyServo() {
    }

    MyServo(int pin, int initPos) {
        servo = new Servo();
        servo->write(initPos);
        servo->attach(pin);
        state = State::Done;
        finalPos = 90;
    }

    void moveToPosition(int finalPos) {
        this->finalPos = finalPos;
        state = State::Working;
    }

    void loop(unsigned long currentTime, int retard = 0) {
        if (isDone()) return;

        int currentPos = servo->read();

        if (currentPos == finalPos) {
            state = State::Done;
        } else {
            if (waiter.isExceeded(currentTime)) {
                if (currentPos < finalPos) {
                    currentPos++;
                } else {
                    currentPos--;
                }
                servo->write(currentPos);
                wait(retard, currentTime);
            }
        }
    }

    void wait(unsigned long waitingTime, unsigned long currentTime) {
        waiter.wait(waitingTime, currentTime);
        state = State::Waiting;
    }

    bool isDone() {
        return state == State::Done;
    }

    bool isWaiting() {
        return state == State::Waiting;
    }

    bool isWorking() {
        return state == State::Working;
    }
};

class ServoTool : public MyServo {
   public:
    using MyServo::MyServo;

    void close() {
        moveToPosition(0);
    }

    void open() {
        moveToPosition(180);
    }
};
