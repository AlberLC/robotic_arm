#include "f_servo.h"

#include "f_time.h"

MyServo::MyServo() : Device() {
}

MyServo::MyServo(int pin, int initPos) : Device() {
    servo = new Servo();
    servo->write(initPos);
    servo->attach(pin);
    this->initPos = initPos;
    state = State::Done;
    finalPos = 90;
}

void MyServo::loop(float factor) {
    if (not initLoop()) return;

    int currentPos = round(lerp(startPos, finalPos, (currentTime - startTime) / 1000.f * factor));

    servo->write(currentPos);

    if (currentPos == finalPos) {
        state = State::Done;
    }
}

void MyServo::loopSpeed(float speed) {
    loop(speed / 180);
}

void MyServo::loopTime(float seconds) {
    loop(1 / seconds);
}

void MyServo::moveToPosition(int finalPos) {
    startPos = servo->read();
    this->finalPos = finalPos;
    startTime = currentTime;
    state = State::Working;
}

void MyServo::moveToInitialPosition() {
    moveToPosition(initPos);
}

void ServoTool::close() {
    moveToPosition(0);
}

void ServoTool::open() {
    moveToPosition(180);
}
