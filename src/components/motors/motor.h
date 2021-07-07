#pragma once

#include "../../globals/time.h"
#include "../../utils/math.h"
#include "../../utils/stateful.h"
#include "../component.h"

class Motor : public Stateful, public Component {
   protected:
    int initPos;
    int minPos;
    int maxPos;
    bool inInitPos;
    int startPos;
    float currentPos;
    int roundedCurrentPos;
    int finalPos;
    int midPos;
    int distance;
    int direction;
    unsigned long elapsedSeconds;
    float currentSpeed;
    float speed;
    float acceleration;
    bool midCrossed;
    float timeToMid;

    float calculateNewPos();
    float calculateTimeToMidUnlimited();
    float calculateTimeToMaxSpeed();
    float calculateDistanceToMaxSpeed();
    void updateTimeToMid();
    void updateSpeed();
    void virtual writeMotor();

   public:
    using Component::Component;
    Motor(int pin, int initPos, int minPos = -1, int maxPos = -1);

    int getMinPos();
    void setMinPos(int minPos);
    int getMaxPos();
    void setMaxPos(int maxPos);
    int getInitPos();
    void setInitPos(int initPos);
    int getCurrentPos();
    float getSpeed();
    void setSpeed(float speed);
    float getDuration();
    void setDuration(float speed);
    float getAcceleration();
    void setAcceleration(float acceleration);
    void loop();
    void moveToPosition(int finalPos);
    void moveToInitialPosition();
    bool isInInitPos();
};