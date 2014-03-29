
#include "EventQueue.h"
#include "TimerEvent.h"

EventQueue::EventQueue() : runningEventLoop(false){
    comsSem.signal();
    handlerSem.signal();
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
    handlerSem.wait();
    timerEventHandlers.push_back(teh);
    handlerSem.signal();
}

void EventQueue::runTimerEventHandlers(TimerEvent& te) {
    handlerSem.wait();
    for(TimerEventHandlerList::size_type i = 0; i < timerEventHandlers.size(); i++) {
        timerEventHandlers[i](te);
    }
    handlerSem.signal();
}
    
void EventQueue::stopEventLoop() {
    comsSem.wait();
    runningEventLoop = false;
    eventSem.signal();
    comsSem.signal();
}

bool EventQueue::test() {
    EventQueue eq;
    bool result = false;
    
    eq.addTimerEventHandler([&](TimerEvent te) {
        result = te.getElapsedTime() == 10;
        eq.stopEventLoop();
    });
    
    eq.pushTimerEvent(10);
    eq.serviceEventLoop();
    
    return result;
}
