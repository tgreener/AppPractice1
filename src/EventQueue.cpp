
#include "EventQueue.h"
#include "TimerEvent.h"

EventQueue::EventQueue() : runningEventLoop(false){
    comsSem.signal();
}

void EventQueue::pushTimerEvent(unsigned long timeElapsed) {
    comsSem.wait();
    timerEvents.push(TimerEvent("TimerEvent", timeElapsed));
    eventSem.signal();
    comsSem.signal();
}

void EventQueue::serviceEventLoop() {
    comsSem.wait();
    runningEventLoop = true;
    comsSem.signal();
    
    while(runningEventLoop) {
        
        if(timerEvents.size() > 0) {
            comsSem.wait();
            TimerEvent te = timerEvents.front();
            timerEvents.pop();
            comsSem.signal();
            
            runTimerEventHandlers(te);
        }
        
        eventSem.wait();
    }
}

void EventQueue::addTimerEventHandler(TimerEventHandler teh) {
    comsSem.wait();
    timerEventHandlers.push_back(teh);
    comsSem.signal();
}

void EventQueue::runTimerEventHandlers(TimerEvent& te) {
    comsSem.wait();
    for(TimerEventHandlerList::size_type i = 0; i < timerEventHandlers.size(); i++) {
        timerEventHandlers[i](te);
    }
    comsSem.signal();
}
    
void EventQueue::stopEventLoop() {
    comsSem.wait();
    runningEventLoop = false;
    comsSem.signal();
}
