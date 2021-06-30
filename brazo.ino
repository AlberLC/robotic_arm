#include "f_config.h"
#include "f_robot.h"
#include "f_time.h"

Robot *robot;
MyButton playPauseButton;
MyButton toolButton;
MyButton stopButton;

void setup() {
    Serial.begin(9600);

    playPauseButton = MyButton(PLAY_PAUSE_BUTTON_PIN);
    toolButton = MyButton(TOOL_BUTTON_PIN);
    stopButton = MyButton(STOP_BUTTON_PIN);

    robot = new Robot();
    robot->setSpeed(ROBOT_SPEED);
    robot->setAcceleration(ROBOT_ACCELERATION);
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
    if (toolButton.pressed()) {
        robot->servoTool.openClose();
    }
    if (stopButton.pressed()) {
        robot->stop();
    }

    Serial.println((int)robot->state);

    robot->testMoveLoop();
}
