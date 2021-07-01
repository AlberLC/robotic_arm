#pragma once

#include "../../../globals/f_config.h"
#include "../../../globals/f_time.h"
#include "../../../utils/f_math.h"
#include "../f_stateful_device.h"
#include "Servo.h"
#include "arduino.h"

class MyServo : public StatefulDevice {
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
