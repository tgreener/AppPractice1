
#include "Timer.h"
#include <thread>
#include <cassert>
#include <dispatch/dispatch.h>

Timer Timer::theTimer;

void Timer::setInterval(unsigned int milliseconds, function<void (void)> callback, bool repeats) {
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
        
        dispatch_source_set_timer(timer, 
                                  dispatch_time(DISPATCH_TIME_NOW, startTime), 
                                  interval, 0);

        dispatch_source_set_event_handler(timer, ^{callback();});
        dispatch_resume(timer);
    }
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
    printf("Testing Timer...\n");
    
    bool result = true;
    
    Semaphore* timerSem = new Semaphore();
    
    Timer* timer = Timer::getTimer();
    
    std::thread thread1(testThread, timer);
    
    int t1c = 0;
    int t2c = 0;
    int t3c = 0;
    int t4c = 0;
    
    auto timeStopperFunc = [&] {
        timerSem->signal();
    };
    
    auto timeFunc1 = [&] {
        t1c++;
    };
    
    auto timeFunc2 = [&] {
        t2c++;
    };
    
    auto timeFunc3 = [&] {
        t3c++;
    };
    
    auto timeFunc4 = [&] {
        t4c++;
    };
    
    timer->setInterval(10050, timeStopperFunc, false);
    timer->setInterval(500, timeFunc2, true);
    timer->setInterval(1000, timeFunc1, true);
    timer->setInterval(2500, timeFunc3, false);
    timer->setInterval(12000, timeFunc4, true);
    
    timerSem->wait();
    delete timerSem;
    
    thread1.join();
    
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