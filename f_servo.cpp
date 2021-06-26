#include "f_servo.h"

#include "f_time.h"

MyServo::MyServo() : Device() {
}

MyServo::MyServo(int pin, int initPos) : Device() {
    state = State::Done;

    inInitPos = true;
    servo = new Servo();
    servo->write(initPos);
    servo->attach(pin);
    this->initPos = initPos;
    startPos = 0;
    finalPos = 0;
    currentPos = 0;
    distance = 0;
    direction = 0;
    startTime = 0;
    finalPos = 90;
    currentSpeed = 0;
    speed = 90;
    acceleration = 1;
}

float MyServo::getSpeed() {
    return speed;
}

void MyServo::setSpeed(float speed) {
    this->speed = speed;
}

float MyServo::getDuration() {
    return distance / speed;
}

void MyServo::setDuration(float duration) {
    speed = distance / duration;
}

float MyServo::getAcceleration() {
    return speed;
}

void MyServo::setAcceleration(float acceleration) {
    this->acceleration = acceleration;
}

int MyServo::getNewPos(float elapsedSeconds) {
    int maxPos;
    int minPos;

    if (direction >= 0) {
        minPos = startPos;
        maxPos = finalPos;
    } else {
        minPos = finalPos;
        maxPos = startPos;
    }

    return constrain(round(startPos + elapsedSeconds * currentSpeed * direction), minPos, maxPos);
}

void MyServo::updateSpeed(float elapsedSeconds) {
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

bool MyServo::initLoop() {
    if (not Device::initLoop()) return false;

    if (acceleration == -1) {
        currentSpeed = speed;
    }

    return true;
}

void MyServo::loop() {
    if (not initLoop()) return;

    float elapsedSeconds = (millis() - startTime) / 1000.f;
    currentPos = getNewPos(elapsedSeconds);

    servo->write(currentPos);

    if (currentPos == finalPos) {
        state = State::Done;
        inInitPos = currentPos == initPos;
    } else if (acceleration != -1) {
        updateSpeed(elapsedSeconds);
    }
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

bool MyServo::isInInitPos() {
    return inInitPos;
}

ServoTool::ServoTool(int pin, int initPos) : MyServo(pin, initPos) {
    toolState = ToolState::Open;
}

void ServoTool::loop() {
    MyServo::loop();

    if (currentPos == 0) {
        toolState = ToolState::Closed;
    } else if (currentPos == 180) {
        toolState = ToolState::FullOpen;
    } else {
        if (toolState != ToolState::Open) {
            toolState = ToolState::Open;
        }
    }
}

void ServoTool::close() {
    moveToPosition(0);
}

void ServoTool::open() {
    moveToPosition(180);
}

void ServoTool::openClose() {
    if (toolState == ToolState::Closed) {
        open();
    } else {
        close();
    }
}

bool ServoTool::isClosed() {
    return toolState == ToolState::Closed;
}

bool ServoTool::isOpen() {
    return toolState == ToolState::Open or
           toolState == ToolState::FullOpen;
}

bool ServoTool::isFullOpen() {
    return toolState == ToolState::FullOpen;
}
