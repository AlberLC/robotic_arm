#include "f_button.cpp"
#include "f_servo.cpp"

ServoTool servoTool;
MyServo servo1;
MyServo servo2;
MyServo servo3;
MyServo servo4;
MyServo servo5;
bool sTGoing = false;
bool s12Going = false;
bool s3Going = false;
bool s4Going = false;
bool s5Going = false;
bool s6Going = false;

void setup() {
    Serial.begin(9600);

    servoTool = ServoTool(8, 90);
    servo1 = MyServo(13, 180);
    servo2 = MyServo(12, 10);
    servo3 = MyServo(11, 180);
    servo4 = MyServo(10, 35);
    servo5 = MyServo(9, 90);
}

void loop() {
    unsigned long currentTime = millis();

    if (servoTool.isDone()) {
        sTGoing = not sTGoing;
        if (sTGoing) {
            servoTool.close();
            servoTool.waitUntil(currentTime + 5000);
        } else {
            servoTool.open();
            servoTool.waitUntil(currentTime + 1000);
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
        servo1.waitUntil(currentTime + 1000);
        servo2.waitUntil(currentTime + 1000);
    }
    if (servo3.isDone()) {
        s3Going = not s3Going;
        if (s3Going) {
            servo3.moveToPosition(90);
        } else {
            servo3.moveToPosition(95);
        }
        servo3.waitUntil(currentTime + 1000);
    }
    if (servo4.isDone()) {
        s4Going = not s4Going;
        if (s4Going) {
            servo4.moveToPosition(10);
        } else {
            servo4.moveToPosition(170);
        }
        servo4.waitUntil(currentTime + 1000);
    }
    if (servo5.isDone()) {
        s5Going = not s5Going;
        if (s5Going) {
            servo5.moveToPosition(130);
        } else {
            servo5.moveToPosition(50);
        }
        servo5.waitUntil(currentTime + 1000);
    }

    servoTool.loop(currentTime, 15);
    servo1.loop(currentTime, 20);
    servo2.loop(currentTime, 20);
    servo3.loop(currentTime, 40);
    servo4.loop(currentTime, 35);
    servo5.loop(currentTime);
}
