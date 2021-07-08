#pragma once

#include "../components/button.h"
#include "../components/motors/servo.h"
#include "../components/motors/stepper.h"
#include "../globals/config.h"
#include "../utils/waiter.h"

class Robot {
   public:
    enum class State { Paused,
                       Waiting,
                       Working };

    Stepper base;

    MyServo servo1;
    MyServo servo2;
    MyServo servo3;
    MyServo servo4;
    MyServo servo5;
    ServoTool servoTool;

    State state;
    Waiter waiter;

    bool s12Going;
    bool s3Going;
    bool s4Going;
    bool s5Going;
    bool goingToInitPos;

    Robot();

    void setSpeed(float speed);
    void setDuration(float duration);
    void setAcceleration(float acceleration);
    bool initLoop();
    void testMoveLoop();
    void loop();
    void play();
    void pause();
    void playPause();
    void stop();
    void wait(unsigned long waitingTime);
    bool isWaiting();
    bool isPaused();
    bool isWorking();
    bool isInInitPos();
};
