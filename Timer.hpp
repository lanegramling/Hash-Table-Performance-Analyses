#include "Timer.h"

void Timer::start() { gettimeofday(&startTime, NULL); }

double Timer::stop() {
    long seconds, nseconds;
    double duration;
    gettimeofday(&endTime, NULL);
    seconds = endTime.tv_sec - startTime.tv_sec;
    nseconds = endTime.tv_usec - startTime.tv_usec;
    duration = seconds + nseconds / 1000000.0;
    return duration;
}

void Timer::printTime(double duration) { printf("%5.6fs\n", duration); }
