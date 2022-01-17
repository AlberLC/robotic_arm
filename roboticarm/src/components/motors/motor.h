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
    int angularDistance;
    int direction;
    unsigned long elapsedSeconds;
    float currentSpeed;
    float speed;
    float acceleration;
    bool midCrossed;
    float timeToMid;

    virtual int calculateAngularDistance(int startPos, int finalPos);
    float calculateNewPos();
    float calculateTimeToMidUnlimited();
    float calculateTimeToMaxSpeed();
    float calculateAngularDistanceToMaxSpeed();
    void updateTimeToMid();
    void updateSpeed();
    virtual void writeMotor(int pos);

   public:
    using Component::Component;
    Motor(int pin, int minPos = UNDEFINED, int maxPos = UNDEFINED);
    Motor(int pin, int initPos, int minPos = UNDEFINED, int maxPos = UNDEFINED);

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