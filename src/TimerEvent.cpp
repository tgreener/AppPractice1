
#include "TimerEvent.h"
#include "ServiceLocator.h"

TimerEvent::TimerEvent(std::string description, unsigned long timeStamp) : 
    timeStamp(timeStamp), Event(description)  {}

long TimerEvent::getElapsedTimeMilli() {
    return NANO_TO_MILLI(getElapsedTimeNano());
}

long TimerEvent::getElapsedTimeNano() {
    Timer* timer = ServiceLocator::getDefaultLocator()->locateTimerService();
    
    return timer->getTimeStamp() - this->timeStamp;
}

