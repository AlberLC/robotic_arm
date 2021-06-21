#pragma once

#include "f_button.h"
#include "f_servo.h"
#include "f_waiter.h"

class Robot {
   public:
    enum class State { Stopped,
                       Waiting,
                       Paused,
                       Working };

    ServoTool servoTool;
    MyServo servo1;
    MyServo servo2;
    MyServo servo3;
    MyServo servo4;
    MyServo servo5;

    State state;
    Waiter waiter;

    bool sTGoing;
    bool s12Going;
    bool s3Going;
    bool s4Going;
    bool s5Going;
    bool s6Going;

    Robot();

    bool initLoop();
    void testMoveLoop();
    void playPause();
    void play();
    void pause();
    void stop();
    void wait(unsigned long waitingTime);
    bool isStopped();
    bool isWaiting();
    bool isPaused();
    bool isWorking();
};
