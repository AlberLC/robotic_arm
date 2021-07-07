#include "robot.h"

Robot::Robot() {
    servoTool = ServoTool(SERVO_TOOL_PIN, SERVO_MIN_POS, SERVO_MAX_POS, SERVO_TOOL_INIT_POS);
    servo1 = MyServo(SERVO_1_PIN, SERVO_MIN_POS, SERVO_MAX_POS, SERVO_1_INIT_POS);
    servo2 = MyServo(SERVO_2_PIN, SERVO_MIN_POS, SERVO_MAX_POS, SERVO_2_INIT_POS);
    servo3 = MyServo(SERVO_3_PIN, SERVO_MIN_POS, SERVO_MAX_POS, SERVO_3_INIT_POS);
    servo4 = MyServo(SERVO_4_PIN, SERVO_MIN_POS, SERVO_MAX_POS, SERVO_4_INIT_POS);
    servo5 = MyServo(SERVO_5_PIN, SERVO_MIN_POS, SERVO_MAX_POS, SERVO_5_INIT_POS);

    state = State::Paused;

    goingToInitPos = false;
    s12Going = false;
    s3Going = false;
    s4Going = false;
    s5Going = false;
}

void Robot::setSpeed(float speed) {
    servoTool.setSpeed(speed);
    servo1.setSpeed(speed);
    servo2.setSpeed(speed);
    servo3.setSpeed(speed);
    servo4.setSpeed(speed);
    servo5.setSpeed(speed);
}

void Robot::setDuration(float duration) {
    servoTool.setDuration(duration);
    servo1.setDuration(duration);
    servo2.setDuration(duration);
    servo3.setDuration(duration);
    servo4.setDuration(duration);
    servo5.setDuration(duration);
}

void Robot::setAcceleration(float acceleration) {
    servoTool.setAcceleration(acceleration);
    servo1.setAcceleration(acceleration);
    servo2.setAcceleration(acceleration);
    servo3.setAcceleration(acceleration);
    servo4.setAcceleration(acceleration);
    servo5.setAcceleration(acceleration);
}

bool Robot::initLoop() {
    if (isPaused() or not waiter.isExceeded()) return false;
    if (goingToInitPos) {
        if (isInInitPos()) {
            goingToInitPos = false;
            pause();
        }
        return false;
    }

    if (state != State::Working) {
        state = State::Working;
    }

    return true;
}

void Robot::testMoveLoop() {
    if (not initLoop()) return;

    if (servoTool.isDone()) {
        if (servoTool.isClosed()) {
            servoTool.open();
            servoTool.wait(5000);
        } else {
            servoTool.close();
            servoTool.wait(1000);
        }
    }
    if (servo1.isDone() and servo2.isDone()) {
        s12Going = not s12Going;
        if (s12Going) {
            servo1.moveToPosition(95);
            servo2.moveToPosition(95);
        } else {
            servo1.moveToPosition(100);
            servo2.moveToPosition(90);
        }
        servo1.wait(1000);
        servo2.wait(1000);
    }
    if (servo3.isDone()) {
        s3Going = not s3Going;
        if (s3Going) {
            servo3.moveToPosition(90);
        } else {
            servo3.moveToPosition(95);
        }
        servo3.wait(1000);
    }
    if (servo4.isDone()) {
        s4Going = not s4Going;
        if (s4Going) {
            servo4.moveToPosition(10);
        } else {
            servo4.moveToPosition(170);
        }
        servo4.wait(1000);
    }
    if (servo5.isDone()) {
        s5Going = not s5Going;
        if (s5Going) {
            servo5.moveToPosition(130);
        } else {
            servo5.moveToPosition(50);
        }
        servo5.wait(1000);
    }

    loop();
}

void Robot::loop() {
    servoTool.loop();
    servo1.loop();
    servo2.loop();
    servo3.loop();
    servo4.loop();
    servo5.loop();
}

void Robot::play() {
    servoTool.play();
    servo1.play();
    servo2.play();
    servo3.play();
    servo4.play();
    servo5.play();

    state = State::Waiting;
}

void Robot::pause() {
    state = State::Paused;

    servoTool.pause();
    servo1.pause();
    servo2.pause();
    servo3.pause();
    servo4.pause();
    servo5.pause();
}

void Robot::playPause() {
    if (state == State::Paused) {
        play();
    } else {
        pause();
    }
}

void Robot::stop() {
    goingToInitPos = true;

    servoTool.moveToInitialPosition();
    servo1.moveToInitialPosition();
    servo2.moveToInitialPosition();
    servo3.moveToInitialPosition();
    servo4.moveToInitialPosition();
    servo5.moveToInitialPosition();
}

void Robot::wait(unsigned long waitingTime) {
    state = State::Waiting;
    waiter.wait(waitingTime);
}

bool Robot::isWaiting() {
    return state == State::Waiting;
}

bool Robot::isPaused() {
    return state == State::Paused;
}

bool Robot::isWorking() {
    return state == State::Working;
}

bool Robot::isInInitPos() {
    return servoTool.isInInitPos() and
           servo1.isInInitPos() and
           servo2.isInInitPos() and
           servo3.isInInitPos() and
           servo4.isInInitPos() and
           servo5.isInInitPos();
}
