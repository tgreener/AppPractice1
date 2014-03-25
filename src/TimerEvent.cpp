
#include "TimerEvent.h"


TimerEvent::TimerEvent(std::string description, unsigned long elapsedTime) : 
    elapsedTime(elapsedTime), Event(description) {}

unsigned long TimerEvent::getElapsedTime() {
    return elapsedTime;
}
