#pragma once

#include "Servo.h"
#include "f_device.cpp"

class MyServo : public Device {
   protected:
    Servo *servo;
    int finalPos;

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

    void loop(unsigned long currentTime, int retard = 0) {
        Device::loop(currentTime, retard);

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
