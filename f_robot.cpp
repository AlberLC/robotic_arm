#include "f_button.cpp"
#include "f_servo.cpp"

class Robot {
   public:
    enum class State { Waiting,
                       Paused,
                       Stopped,
                       Working };

    ServoTool servoTool;
    MyServo servo1;
    MyServo servo2;
    MyServo servo3;
    MyServo servo4;
    MyServo servo5;

    State state;

    bool sTGoing;
    bool s12Going;
    bool s3Going;
    bool s4Going;
    bool s5Going;
    bool s6Going;

    Robot() {
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

    void testMove(unsigned long currentTime) {
        if (servoTool.isDone()) {
            sTGoing = not sTGoing;
            if (sTGoing) {
                servoTool.close();
                servoTool.wait(5000, currentTime);
            } else {
                servoTool.open();
                servoTool.wait(1000, currentTime);
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
            servo1.wait(1000, currentTime);
            servo2.wait(1000, currentTime);
        }
        if (servo3.isDone()) {
            s3Going = not s3Going;
            if (s3Going) {
                servo3.moveToPosition(90);
            } else {
                servo3.moveToPosition(95);
            }
            servo3.wait(1000, currentTime);
        }
        if (servo4.isDone()) {
            s4Going = not s4Going;
            if (s4Going) {
                servo4.moveToPosition(10);
            } else {
                servo4.moveToPosition(170);
            }
            servo4.wait(1000, currentTime);
        }
        if (servo5.isDone()) {
            s5Going = not s5Going;
            if (s5Going) {
                servo5.moveToPosition(130);
            } else {
                servo5.moveToPosition(50);
            }
            servo5.wait(1000, currentTime);
        }

        servoTool.loop(currentTime, 15);
        servo1.loop(currentTime, 20);
        servo2.loop(currentTime, 20);
        servo3.loop(currentTime, 40);
        servo4.loop(currentTime, 35);
        servo5.loop(currentTime);
    }

    void playPause() {
        if (state == State::Paused) {
            play();
        } else {
            pause();
        }
    }

    void play() {
        servoTool.play();
        servo1.play();
        servo2.play();
        servo3.play();
        servo4.play();
        servo5.play();
    }

    void pause() {
        servoTool.pause();
        servo1.pause();
        servo2.pause();
        servo3.pause();
        servo4.pause();
        servo5.pause();
    }

    void stop() {
        servoTool.stop();
        servo1.stop();
        servo2.stop();
        servo3.stop();
        servo4.stop();
        servo5.stop();
    }
};
