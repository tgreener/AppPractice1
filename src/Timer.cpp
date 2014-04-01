
#include "Timer.h"
#include <thread>
#include <cassert>
#include <mach/mach_time.h>

Timer Timer::theTimer;

TimerInterval Timer::setInterval(unsigned int milliseconds, function<void (unsigned long ts)> callback, bool repeats) {
    dispatch_source_t timer = 
            dispatch_source_create(DISPATCH_SOURCE_TYPE_TIMER, 
            0, 0, dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0));

    if (timer)
    {
        unsigned long startTime = (MILLI_TO_NANO(milliseconds));
        
        unsigned long interval;
        if(repeats) {
            interval = (MILLI_TO_NANO(milliseconds));
        }
        else {
            interval = DISPATCH_TIME_FOREVER;
        }
        
        __block unsigned long ts = this->getTimeStamp();
        dispatch_source_set_timer(timer, 
                                  dispatch_time(DISPATCH_TIME_NOW, startTime), 
                                  interval, 1000);

        dispatch_source_set_event_handler(timer, ^{
            callback(ts);
            ts = this->getTimeStamp();
        });
        dispatch_resume(timer);
    }
    else {
        timer = NULL;
    }
    
    return timer;
}

unsigned long Timer::getTimeStamp() {
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    
    unsigned long ts = mach_absolute_time();
    
    ts *= info.numer;
    ts /= info.denom;
    
    return ts;
}

Timer* Timer::getTimer() {
    return &theTimer;
}

Timer::Timer() {
    comsSem.signal();
}

void testThread(Timer* timer) {
    Timer* threadTimer = Timer::getTimer();
    
    assert(timer == threadTimer);
}

bool Timer::test() {
    bool result = true;
    
    Semaphore* timerSem = new Semaphore();
    
    Timer* timer = Timer::getTimer();
    
    std::thread thread1(testThread, timer);
    
    int t1c = 0;
    int t2c = 0;
    int t3c = 0;
    int t4c = 0;
    
    auto timeStopperFunc = [&] (unsigned long ts) {
        timerSem->signal();
    };
    
    auto timeFunc1 = [&] (unsigned long ts) {
        t1c++;
    };
    
    auto timeFunc2 = [&] (unsigned long ts) {
        t2c++;
    };
    
    auto timeFunc3 = [&] (unsigned long ts) {
        t3c++;
    };
    
    auto timeFunc4 = [&] (unsigned long ts) {
        t4c++;
    };
    
    auto progress = [] (unsigned long ts) {
        printf(".");
        fflush(stdout);
    };
    
    TimerInterval interval1 = timer->setInterval(10050, timeStopperFunc, false);
    TimerInterval interval2 = timer->setInterval(500, timeFunc2, true);
    TimerInterval interval3 = timer->setInterval(1000, timeFunc1, true);
    TimerInterval interval4 = timer->setInterval(2500, timeFunc3, false);
    TimerInterval interval5 = timer->setInterval(12000, timeFunc4, true);
    TimerInterval interval6 = timer->setInterval(2000, progress, true);
    
    timerSem->wait();
    delete timerSem;
    
    thread1.join();

    interval1.cancel();
    interval2.cancel();
    interval3.cancel();
    interval4.cancel();
    interval5.cancel();
    interval6.cancel();
    
    int t1cExpected = 10;
    int t2cExpected = 20;
    int t3cExpected = 1;
    int t4cExpected = 0;
    
    if(t1c != t1cExpected) {
        printf("Var t1c, expected: %d actual: %d\n", t1cExpected, t1c);
        result = false;
    }
    
    if(t2c != t2cExpected) {
        printf("Var t2c, expected: %d actual: %d\n", t2cExpected, t2c);
        result = false;
    }
    
    if(t3c != t3cExpected) {
        printf("Var t3c, expected: %d actual: %d\n", t3cExpected, t3c);
        result = false;
    }
    
    if(t4c != t4cExpected) {
        printf("Var t4c, expected: %d actual: %d\n", t4cExpected, t4c);
        result = false;
    }
    
    return result;
}