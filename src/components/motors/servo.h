#pragma once

#include <Servo.h>

#include "motor.h"

class MyServo : public Motor {
   protected:
    Servo *servo;

   public:
    using Motor::Motor;
    MyServo(int pin, int initPos, int minPos = -1, int maxPos = -1);

    void writeMotor() override;
};

class ServoTool : public MyServo {
   protected:
    enum class ToolState { Closed,
                           Open,
                           FullOpen };
    ToolState toolState;

   public:
    using MyServo::MyServo;
    ServoTool(int pin, int initPos, int minPos = -1, int maxPos = -1);

    void loop();
    void close();
    void open();
    void openClose();
    bool isClosed();
    bool isOpen();
    bool isFullOpen();
};
