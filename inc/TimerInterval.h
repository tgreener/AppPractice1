/* 
 * File:   TimerInterval.h
 * Author: toddgreener
 *
 * Created on March 17, 2014, 11:49 PM
 */

#ifndef TIMERINTERVAL_H
#define	TIMERINTERVAL_H

#include <dispatch/dispatch.h>

class TimerInterval {
private:
    dispatch_source_t dispatchInterval;
public:
    TimerInterval(dispatch_source_t di);
    void cancel();
};

#endif	/* TIMERINTERVAL_H */

