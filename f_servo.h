#pragma once

#include "Servo.h"
#include "arduino.h"
#include "f_config.h"
#include "f_device.h"
#include "f_math.h"

class MyServo : public Device {
   protected:
    Servo *servo;
    bool inInitPos;
    int initPos;
    int startPos;
    int currentPos;
    int finalPos;
    int midPos;
    int distance;
    int direction;
    unsigned long startTime;
    float currentSpeed;
    float speed;
    float acceleration;
    bool midCrossed;
    float timeToMid;

    int getNewPos(float elapsedSeconds);
    float getTimeToMid();
    float getTimeToMaxSpeed();
    float getDistanceToMaxSpeed();
    void updateSpeed(float elapsedSeconds);

   public:
    MyServo() = default;
    MyServo(int pin, int initPos);

    float getSpeed();
    void setSpeed(float speed);
    float getDuration();
    void setDuration(float speed);
    float getAcceleration();
    void setAcceleration(float acceleration);
    void virtual loop();
    void moveToPosition(int finalPos);
    void moveToInitialPosition();
    bool isInInitPos();
};

class ServoTool : public MyServo {
   protected:
    enum class ToolState { Closed,
                           Open,
                           FullOpen };
    ToolState toolState;

   public:
    using MyServo::MyServo;
    ServoTool(int pin, int initPos);

    void loop() override;
    void close();
    void open();
    void openClose();
    bool isClosed();
    bool isOpen();
    bool isFullOpen();
};
