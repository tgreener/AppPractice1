/* 
 * File:   TimerEvent.h
 * Author: toddgreener
 *
 * Created on March 24, 2014, 10:14 PM
 */

#ifndef TIMEREVENT_H
#define	TIMEREVENT_H

#include "Event.h"

class TimerEvent : public Event {
private:
    long timeStamp;
public:
    TimerEvent(std::string description, unsigned long timeStamp);
    long getElapsedTimeMilli();
    long getElapsedTimeNano();
};

#endif	/* TIMEREVENT_H */

