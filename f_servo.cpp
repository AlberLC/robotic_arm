#pragma once

#include "Servo.h"
#include "f_device.cpp"

class MyServo : public Device {
   protected:
    Servo *servo;
    int finalPos;

    void _loop() {
        int currentPos = servo->read();

        if (currentPos < finalPos) {
            currentPos++;
        } else {
            currentPos--;
        }

        servo->write(currentPos);

        if (currentPos == finalPos) {
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
        state = State::Done;
        finalPos = 90;
    }

    void moveToPosition(int finalPos) {
        this->finalPos = finalPos;
        state = State::Working;
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
