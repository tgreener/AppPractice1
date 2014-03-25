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
    unsigned long elapsedTime;
public:
    TimerEvent(std::string description, unsigned long elapsedTime);
    unsigned long getElapsedTime();
};

#endif	/* TIMEREVENT_H */

