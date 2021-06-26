#include "f_robot.h"
#include "f_time.h"

Robot *robot;
MyButton playPauseButton;
MyButton ToolButton;
MyButton StopButton;

void setup() {
    Serial.begin(9600);

    playPauseButton = MyButton(7);
    ToolButton = MyButton(6);
    StopButton = MyButton(5);

    robot = new Robot();
    robot->setSpeed(90);
    robot->setAcceleration(-1);
    // robot->servoTool.setSpeed(90);
    // robot->servo1.setSpeed(90);
    // robot->servo2.setSpeed(90);
    // robot->servo3.setSpeed(90);
    // robot->servo4.setSpeed(90);
    // robot->servo5.setSpeed(90);

    // robot->servoTool.setAcceleration(-1);
    // robot->servo1.setAcceleration(-1);
    // robot->servo2.setAcceleration(-1);
    // robot->servo3.setAcceleration(-1);
    // robot->servo4.setAcceleration(-1);
    // robot->servo5.setAcceleration(-1);
}

void loop() {
    Time::update(millis());

    if (playPauseButton.pressed()) {
        robot->playPause();
    }
    if (ToolButton.pressed()) {
        robot->servoTool.openClose();
    }
    if (StopButton.pressed()) {
        robot->stop();
    }

    Serial.println((int)robot->state);

    robot->testMoveLoop();
}
