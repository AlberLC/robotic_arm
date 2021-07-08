#include "src/components/potentiometer.h"
#include "src/globals/config.h"
#include "src/globals/time.h"
#include "src/robots/robot.h"

Robot* robot;
MyButton playPauseButton;
MyButton toolButton;
MyButton stopButton;
Potentiometer potentiometer;

void setup() {
    Serial.begin(9600);

    playPauseButton = MyButton(PLAY_PAUSE_BUTTON_PIN);
    toolButton = MyButton(TOOL_BUTTON_PIN);
    stopButton = MyButton(STOP_BUTTON_PIN);

    robot = new Robot();
    robot->setSpeed(ROBOT_SPEED);
    robot->setAcceleration(ROBOT_ACCELERATION);

    // potentiometer = Potentiometer(POTENTIOMETER_PIN, POTENTIOMETER_MIN_LIMIT, POTENTIOMETER_MAX_LIMIT);
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

    // Serial.println(potentiometer.read());

    //robot->testMoveLoop();
}
