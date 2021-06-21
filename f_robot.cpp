#include "f_robot.h"

Robot::Robot() {
    servoTool = ServoTool(8, 90);
    servo1 = MyServo(13, 180);
    servo2 = MyServo(12, 10);
    servo3 = MyServo(11, 180);
    servo4 = MyServo(10, 35);
    servo5 = MyServo(9, 90);

    state = State::Stopped;

    sTGoing = false;
    s12Going = false;
    s3Going = false;
    s4Going = false;
    s5Going = false;
    s6Going = false;
}

bool Robot::initLoop() {
    if (isStopped() or isPaused() or not waiter.isExceeded()) return false;

    if (state != State::Working) {
        state = State::Working;
    }

    return true;
}

void Robot::testMoveLoop() {
    if (not initLoop()) return;

    if (servoTool.isDone()) {
        sTGoing = not sTGoing;
        if (sTGoing) {
            servoTool.close();
            servoTool.wait(5000);
        } else {
            servoTool.open();
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

    servoTool.loopSpeed(15);
    servo1.loopSpeed(20);
    servo2.loopSpeed(20);
    servo3.loopSpeed(40);
    servo4.loopSpeed(35);
    servo5.loopSpeed();
}

void Robot::playPause() {
    if (state == State::Paused) {
        play();
    } else {
        pause();
    }
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

void Robot::stop() {
    state = State::Stopped;

    servoTool.stop();
    servo1.stop();
    servo2.stop();
    servo3.stop();
    servo4.stop();
    servo5.stop();
}

void Robot::wait(unsigned long waitingTime) {
    state = State::Waiting;
    waiter.wait(waitingTime);
}

bool Robot::isStopped() {
    return state == State::Stopped;
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
