#pragma once

class Time {
   public:
    static unsigned long currentTime;
    static unsigned long deltaTime;

    static void update(unsigned long currentTime);
};