#include "f_robot.cpp"

Robot robot;

void setup() {
    Serial.begin(9600);
}

void loop() {
    unsigned long currentTime = millis();

    robot.testMoveLoop(currentTime);
}
