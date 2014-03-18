/* 
 * File:   TimerService.h
 * Author: toddgreener
 *
 * Created on March 11, 2014, 12:36 AM
 */

#ifndef TIMER_H
#define	TIMER_H

#define D_CLOCK_SIZE 256
#define MICRO_TO_NANO(ms) ms * 1000L
#define MILLI_TO_MICRO(mls) mls * 1000L
#define MILLI_TO_NANO(mls) mls * 1000000L
#define SEC_TO_NANO(s) s * 1000000000L

#include <stdlib.h>
#include <time.h>
#include <functional>
#include "Semaphore.h"

class Timer {
private:
    Semaphore timerSem;
    Semaphore comsSem;
    
    static Timer theTimer;
    
    Timer();
public:
    void setInterval(unsigned int milliseconds, function<void (void)> callback, bool repeats);
    
    static Timer* getTimer();
    static bool test();
};

#endif	/* TIMERSERVICE_H */

