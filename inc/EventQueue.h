/* 
 * File:   EventQueue.h
 * Author: toddgreener
 *
 * Created on March 19, 2014, 2:19 PM
 */

#ifndef EVENTQUEUE_H
#define	EVENTQUEUE_H

#include "Event.h"
#include <queue>

typedef std::queue<Event> EventList;

class EventQueue {
private:
    EventList events;
public:
    void pushTimerEvent(unsigned long timeElapsed);
    Event pullEvent();
};

#endif	/* EVENTQUEUE_H */

