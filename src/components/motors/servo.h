#pragma once

#include <Servo.h>

#include "motor.h"

class MyServo : public Motor {
   protected:
    Servo *servo;

    int calculateAngularDistance(int startPos, int finalPos) override;

   public:
    using Motor::Motor;
    MyServo(int pin, int minPos = UNDEFINED, int maxPos = UNDEFINED);
    MyServo(int pin, int initPos, int minPos = UNDEFINED, int maxPos = UNDEFINED);

    void setPin(int pin);
    void writeMotor(int pos) override;
};

class ServoTool : public MyServo {
   protected:
    enum class ToolState { Closed,
                           Open,
                           FullOpen };
    ToolState toolState;

   public:
    using MyServo::MyServo;
    ServoTool(int pin, int minPos = UNDEFINED, int maxPos = UNDEFINED);
    ServoTool(int pin, int initPos, int minPos = UNDEFINED, int maxPos = UNDEFINED);

    void loop();
    void close();
    void open();
    void openClose();
    bool isClosed();
    bool isOpen();
    bool isFullOpen();
};
