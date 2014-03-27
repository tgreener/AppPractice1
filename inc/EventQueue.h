/* 
 * File:   EventQueue.h
 * Author: toddgreener
 *
 * Created on March 19, 2014, 2:19 PM
 */

#ifndef EVENTQUEUE_H
#define	EVENTQUEUE_H

#include "Event.h"
#include "TimerEvent.h"
#include "Semaphore.h"
#include <queue>
#include <functional>
#include <vector>

typedef std::queue<TimerEvent> TimerEventQueue;
typedef std::function<void (TimerEvent)> TimerEventHandler;
typedef std::vector<std::function<void (TimerEvent)> > TimerEventHandlerList;

class EventQueue {
private:
    TimerEventQueue timerEvents;
    Semaphore eventSem;
    Semaphore comsSem;
    Semaphore handlerSem;
    
    bool runningEventLoop;
    
    TimerEventHandlerList timerEventHandlers;
    
    void runTimerEventHandlers(TimerEvent& te);
public:
    EventQueue();
    
    void pushTimerEvent(unsigned long timeElapsed);
    void serviceEventLoop();
    void addTimerEventHandler(TimerEventHandler teh);
    
    void stopEventLoop();
    
    static bool test();
};

#endif	/* EVENTQUEUE_H */

