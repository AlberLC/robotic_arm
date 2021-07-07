#include "motor.h"

Motor::Motor(int pin, int initPos, int minPos, int maxPos) : Component(pin), Stateful() {
    state = State::Done;

    this->initPos = initPos;
    this->minPos = minPos;
    this->maxPos = maxPos;
    inInitPos = true;
    startPos = initPos;
    currentPos = initPos;
    roundedCurrentPos = initPos;
    finalPos = initPos;
    midPos = (startPos + finalPos) / 2;
    angularDistance = 0;
    direction = 0;
    elapsedSeconds = 0;
    currentSpeed = 0;
    speed = 90;
    acceleration = 30;
    midCrossed = false;
    updateTimeToMid();
}

int Motor::getMinPos() {
    return minPos;
}

void Motor::setMinPos(int minPos) {
    this->minPos = minPos;
}

int Motor::getMaxPos() {
    return maxPos;
}

void Motor::setMaxPos(int maxPos) {
    this->maxPos = maxPos;
}

int Motor::getInitPos() {
    return initPos;
}

void Motor::setInitPos(int initPos) {
    this->initPos = initPos;
}

int Motor::getCurrentPos() {
    return roundedCurrentPos;
}

float Motor::getSpeed() {
    return speed;
}

void Motor::setSpeed(float speed) {
    if (this->speed != speed) {
        this->speed = speed;
        updateTimeToMid();
    }
}

float Motor::getDuration() {
    return angularDistance / speed;
}

void Motor::setDuration(float duration) {
    float speed = angularDistance / duration;
    setSpeed(speed);
}

float Motor::getAcceleration() {
    return speed;
}

void Motor::setAcceleration(float acceleration) {
    if (this->acceleration != acceleration) {
        this->acceleration = acceleration;
        updateTimeToMid();
    }
}

int Motor::calculateDistance() {
}

float Motor::calculateNewPos() {
    int maxPos;
    int minPos;

    if (direction >= 0) {
        minPos = startPos;
        maxPos = finalPos;
    } else {
        minPos = finalPos;
        maxPos = startPos;
    }

    return constrain(currentPos + Time::deltaTime / 1000.f * currentSpeed * direction, minPos, maxPos);
}

float Motor::calculateTimeToMidUnlimited() {
    return sqrt(abs(2 * acceleration * (midPos - startPos))) / acceleration;
}

float Motor::calculateTimeToMaxSpeed() {
    return speed / acceleration;
}

float Motor::calculateDistanceToMaxSpeed() {
    return speed * speed / (2 * acceleration);
}

void Motor::updateTimeToMid() {
    timeToMid = calculateTimeToMidUnlimited();
    float timeToMaxSpeed = calculateTimeToMaxSpeed();
    if (timeToMaxSpeed < timeToMid) {
        timeToMid = timeToMaxSpeed + (abs(midPos - startPos) - calculateDistanceToMaxSpeed()) / speed;
    }
}

void Motor::updateSpeed() {
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

void Motor::writeMotor(int pos) {
}

void Motor::loop() {
    if (not initLoop()) return;

    elapsedSeconds += Time::deltaTime / 1000.f;

    if (acceleration == UNDEFINED) {
        if (currentSpeed != speed) {
            currentSpeed = speed;
        }
    } else {
        updateSpeed();
        currentSpeed = constrain(currentSpeed, 0, speed);
    }

    currentPos = calculateNewPos();
    roundedCurrentPos = round(currentPos);
    writeMotor(roundedCurrentPos);

    if (roundedCurrentPos == finalPos) {
        state = State::Done;
        inInitPos = initPos == finalPos;
    }
}

void Motor::moveToPosition(int finalPos) {
    startPos = roundedCurrentPos;
    int d = calculateDistance(startPos, finalPos);
    angularDistance = abs(d);
    direction = sign(d);
    elapsedSeconds = 0;
    state = State::Working;
    currentSpeed = 0;
    updateTimeToMid();
}

void Motor::moveToInitialPosition() {
    moveToPosition(initPos);
}

bool Motor::isInInitPos() {
    return inInitPos;
}