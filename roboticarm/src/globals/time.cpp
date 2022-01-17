#include "time.h"

unsigned long Time::currentTime = 0;
unsigned long Time::deltaTime = 0;

void Time::update(unsigned long currentTime) {
    Time::deltaTime = currentTime - Time::currentTime;
    Time::currentTime = currentTime;
}