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
    currentSpeed = 0;
}

void MyServo::updateSpeed(float speed, float elapsedSeconds, int currentPos, float acceleration) {
    int degreeToSlowDown = -1;
    int halfPoint = (startPos + finalPos) / 2;

    if (currentPos < halfPoint and currentSpeed != speed) {
        currentSpeed = acceleration * elapsedSeconds;
        if (currentSpeed >= speed) {
            currentSpeed = speed;
            degreeToSlowDown = finalPos - (currentPos - startPos);
        }
    } else if ((degreeToSlowDown == -1 or (startPos <= finalPos and currentPos >= degreeToSlowDown) or (startPos > finalPos and currentPos <= degreeToSlowDown)) and currentSpeed > 0) {
        currentSpeed -= acceleration * Time::deltaTime / 1000.f;
        if (currentSpeed <= 0) {
            currentSpeed = 0;
        }
    }
}

bool MyServo::initLoop(float speed, float acceleration) {
    if (not Device::initLoop()) return false;

    if (acceleration == -1) {
        currentSpeed = speed;
    }

    return true;
}

void MyServo::loop(float speed, float acceleration) {
    if (not initLoop(speed, acceleration)) return;

    float elapsedSeconds = (Time::currentTime - startTime) / 1000.f;
    int currentPos = round(lerp(startPos, finalPos, elapsedSeconds * currentSpeed));

    servo->write(currentPos);

    if (currentPos == finalPos) {
        state = State::Done;
    } else if (acceleration != -1) {
        updateSpeed(speed, elapsedSeconds, currentPos, acceleration);
    }
}

void MyServo::loopSpeed(float speed, float acceleration) {
    loop(distance / speed / 180, acceleration);
}

void MyServo::loopTime(float seconds, float acceleration) {
    loop(1 / seconds, acceleration);
}

void MyServo::moveToPosition(int finalPos) {
    startPos = servo->read();
    this->finalPos = finalPos;
    distance = abs(finalPos - startPos);
    startTime = Time::currentTime;
    state = State::Working;
    currentSpeed = 0;
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
