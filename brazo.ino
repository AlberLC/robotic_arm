#include "f_robot.h"
#include "f_time.h"

Robot robot;

void setup() {
    Serial.begin(9600);
}

void loop() {
    Time::update(millis());

    robot.testMoveLoop();
    robot.stop();
}
