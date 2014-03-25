
#include "EventQueue.h"
#include "TimerEvent.h"

void EventQueue::pushTimerEvent(unsigned long timeElapsed) {
    events.push(TimerEvent("TimerEvent", timeElapsed));
}

Event EventQueue::pullEvent() {
    Event e = events.front();
    events.pop();
    
    return e;
}
