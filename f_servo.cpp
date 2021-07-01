#include "f_servo.h"

MyServo::MyServo(int pin, int initPos) : Device() {
    state = State::Done;

    inInitPos = true;
    servo = new Servo();
    servo->write(initPos);
    servo->attach(pin);
    this->initPos = initPos;
    startPos = initPos;
    currentPos = initPos;
    finalPos = initPos;
    midPos = (startPos + finalPos) / 2;
    distance = 0;
    direction = 0;
    startTime = 0;
    currentSpeed = 0;
    speed = 90;
    acceleration = 30;
    midCrossed = false;
    timeToMid = getTimeToMid();
    float timeToMaxSpeed = getTimeToMaxSpeed();
    if (timeToMaxSpeed < timeToMid) {
        timeToMid = timeToMaxSpeed + (midPos - getDistanceToMaxSpeed()) / speed;
    }
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

    return constrain(round(currentPos + Time::deltaTime / 1000.f * currentSpeed * direction), minPos, maxPos);
}

float MyServo::getTimeToMid() {
    return sqrt(abs(2 * acceleration * (midPos - startPos))) / acceleration;
}

float MyServo::getTimeToMaxSpeed() {
    return speed / acceleration;
}

float MyServo::getDistanceToMaxSpeed() {
    return (speed * speed) / (2 * acceleration);
}

void MyServo::updateSpeed(float elapsedSeconds) {
    if (elapsedSeconds < timeToMid) {
        currentSpeed += Time::deltaTime / 1000.f * acceleration;
    } else if (not midCrossed) {
        midCrossed = true;
        float t2 = elapsedSeconds - timeToMid;
        float t1 = Time::deltaTime / 1000.f - t2;
        currentSpeed += t1 * acceleration - t2 * acceleration;
    } else {
        currentSpeed -= Time::deltaTime / 1000.f * acceleration;
    }
}

void MyServo::loop() {
    if (not initLoop()) return;

    float elapsedSeconds = (Time::currentTime - startTime) / 1000.f;
    if (acceleration == UNDEFINED) {
        if (currentSpeed != speed) {
            currentSpeed = speed;
        }
    } else {
        updateSpeed(elapsedSeconds);
        currentSpeed = constrain(currentSpeed, 0, speed);
    }

    currentPos = getNewPos(elapsedSeconds);
    servo->write(currentPos);

    if (currentPos == finalPos) {
        state = State::Done;
        inInitPos = currentPos == initPos;
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
    } else if (currentPos == SERVO_MAX_POS) {
        toolState = ToolState::FullOpen;
    } else if (not isOpen()) {
        toolState = ToolState::Open;
    }
}

void ServoTool::close() {
    moveToPosition(0);
}

void ServoTool::open() {
    moveToPosition(SERVO_MAX_POS);
}

void ServoTool::openClose() {
    if (isClosed()) {
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
