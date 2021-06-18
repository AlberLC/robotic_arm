#pragma once

#include "Servo.h"
#include "f_device.cpp"

class MyServo : public Device {
   protected:
    Servo *servo;
    int initPos;
    int finalPos;

    void _loop() {
        int currentPos = servo->read();

        if (currentPos < finalPos) {
            servo->write(currentPos + 1);
        } else if (currentPos > finalPos) {
            servo->write(currentPos - 1);
        } else {
            state = State::Done;
        }
    }

   public:
    MyServo() : Device() {
    }

    MyServo(int pin, int initPos) : Device() {
        servo = new Servo();
        servo->write(initPos);
        servo->attach(pin);
        this->initPos = initPos;
        state = State::Done;
        finalPos = 90;
    }

    void moveToPosition(int finalPos) {
        this->finalPos = finalPos;
        state = State::Working;
    }

    void moveToInitialPosition() {
        moveToPosition(initPos);
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
