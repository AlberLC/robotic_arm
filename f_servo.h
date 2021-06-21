#pragma once

#include "Servo.h"
#include "arduino.h"
#include "f_device.h"
#include "f_math.h"

class MyServo : public Device {
   protected:
    Servo *servo;
    int initPos;
    int startPos;
    int finalPos;
    unsigned long startTime;

    void loop(float todo);

   public:
    MyServo();
    MyServo(int pin, int initPos);

    void loopSpeed(float speed = 1);
    void loopTime(float seconds = 2);
    void moveToPosition(int finalPos);
    void moveToInitialPosition();
};

class ServoTool : public MyServo {
   public:
    using MyServo::MyServo;

    void close();
    void open();
};
