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
    float currentSpeed;

    bool initLoop(float speed, float acceleration);
    void loop(float speed, float acceleration);
    void updateSpeed(float speed, float elapsedSeconds, int currentPos, float acceleration);

   public:
    MyServo();
    MyServo(int pin, int initPos);

    void loopSpeed(float speed = 1, float acceleration = 1);
    void loopTime(float seconds = 2, float acceleration = 1);
    void moveToPosition(int finalPos);
    void moveToInitialPosition();
};

class ServoTool : public MyServo {
   public:
    using MyServo::MyServo;

    void close();
    void open();
};
