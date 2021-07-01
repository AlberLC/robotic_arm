#pragma once

#include "../components/f_button.h"
#include "../components/stateful_devices/motors/f_servo.h"
#include "../globals/f_config.h"
#include "../utils/f_waiter.h"

class Robot {
   public:
    enum class State { Paused,
                       Waiting,
                       Working };

    ServoTool servoTool;
    MyServo servo1;
    MyServo servo2;
    MyServo servo3;
    MyServo servo4;
    MyServo servo5;

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
