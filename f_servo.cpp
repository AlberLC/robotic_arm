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

int MyServo::getNewPos(float elapsedSeconds) {
    int maxPos;
    int minPos;

    if (startPos <= finalPos) {
        minPos = startPos;
        maxPos = finalPos;
    } else {
        minPos = finalPos;
        maxPos = startPos;
    }

    return constrain(round(startPos + elapsedSeconds * currentSpeed * direction), minPos, maxPos);
}

void MyServo::updateSpeed(float speed, float elapsedSeconds, int pos, float acceleration) {
    int degreeToSlowDown = -1;
    int halfPoint = (startPos + finalPos) / 2;

    if (pos < halfPoint and currentSpeed != speed) {
        currentSpeed = acceleration * elapsedSeconds;
        if (currentSpeed >= speed) {
            currentSpeed = speed;
            degreeToSlowDown = finalPos - (pos - startPos);
        }
    } else if ((degreeToSlowDown == -1 or (startPos <= finalPos and pos >= degreeToSlowDown) or (startPos > finalPos and pos <= degreeToSlowDown)) and currentSpeed > 0) {
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
    int pos = getNewPos(elapsedSeconds);

    servo->write(pos);

    if (pos == finalPos) {
        state = State::Done;
    } else if (acceleration != -1) {
        updateSpeed(speed, elapsedSeconds, pos, acceleration);
    }
}

void MyServo::loopSpeed(float speed, float acceleration) {
    loop(speed, acceleration);
}

void MyServo::loopTime(float seconds, float acceleration) {
    loop(distance / seconds, acceleration);
}

void MyServo::moveToPosition(int finalPos) {
    startPos = servo->read();
    this->finalPos = finalPos;
    int d = finalPos - startPos;
    distance = abs(d);
    direction = sign(d);
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
