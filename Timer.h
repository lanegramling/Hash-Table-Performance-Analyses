#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

class Timer
{
private:
    timeval startTime;
    timeval endTime;
public:
    void start();
    double stop();
    void printTime(double duration);
};

#include "Timer.hpp"

#endif TIMER_H
