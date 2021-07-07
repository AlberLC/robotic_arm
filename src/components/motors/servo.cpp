#include "servo.h"

MyServo::MyServo(int pin, int initPos, int minPos, int maxPos) : Motor(pin, initPos, minPos, maxPos) {
    servo = new Servo();
    servo->write(initPos);
    servo->attach(pin);
}

int MyServo::calculateDistance(int startPos, int finalPos) {
    return finalPos - startPos;
}

void MyServo::writeMotor(int pos) {
    servo->write(pos);
}

ServoTool::ServoTool(int pin, int initPos, int minPos, int maxPos) : MyServo(pin, initPos, minPos, maxPos) {
    toolState = ToolState::Open;
}

void ServoTool::loop() {
    MyServo::loop();

    if (roundedCurrentPos == getMinPos()) {
        toolState = ToolState::Closed;
    } else if (roundedCurrentPos == getMaxPos()) {
        toolState = ToolState::FullOpen;
    } else if (not isOpen()) {
        toolState = ToolState::Open;
    }
}

void ServoTool::close() {
    moveToPosition(getMinPos());
}

void ServoTool::open() {
    moveToPosition(getMaxPos());
}

void ServoTool::openClose() {
    if (isDone()) {
        if (isClosed()) {
            open();
        } else {
            close();
        }
    } else {
        if (direction < 0) {
            open();
        } else {
            close();
        }
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
