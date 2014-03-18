/* 
 * File:   Application.h
 * Author: toddgreener
 *
 * Created on March 17, 2014, 9:25 AM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

#include <thread>
#include <functional>
#include "Semaphore.h"

class Application {
private:
    std::thread appThread;
    
    Semaphore appSem;
    Semaphore dataSem;
    
    bool running;
    
    void setRunning(bool val);
    void runLoop();
    
public:
    Application();
    
    void run();
    void run(std::function<void (void)> appStartFunction);
    
    void stop();
    
    static bool test();
};

#endif	/* APPLICATION_H */

