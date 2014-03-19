/* 
 * File:   main.cpp
 * Author: toddgreener
 *
 * Created on March 10, 2014, 3:37 PM
 */

#include <cstdlib>
#include <Block.h>
#include "ServiceLocator.h"
#include "Timer.h"
#include "Application.h"

using namespace std;

void printTestResult(bool result) {
    if(result) {
        printf("SUCCESS!\n");
    }
    else {
        printf("FAILED!\n");
    }
}

bool integrationTest() {
    Application app;
    bool result = false;
    
    auto appInit = [&] {
        new thread([&] {
            Semaphore testSem;            
            ServiceLocator* loc = ServiceLocator::getDefaultLocator();

            MessageService* ms = loc->locateMessageService();
            ms->subscribe("timerEvent", [&](StringMap p) { 
                result = true; 
                testSem.signal();
            });
            
            Timer* timer = loc->locateTimerService();
            TimerInterval t1 = timer->setInterval(500, [&]{ ms->publish("timerEvent", StringMap()); }, false);

            testSem.wait();

            t1.cancel();
            app.stop();
        });
    };
    
    app.run(appInit);
    
    return result;
}

/*
 * 
 */
int main(int argc, char** argv) {
    printf("Testing Application...\t\t");
    fflush(stdout);
    printTestResult(Application::test());
    
    printf("Testing ServiceLocator...\t");
    fflush(stdout);
    printTestResult(ServiceLocator::test());
    
    printf("Testing MessageService...\t");
    fflush(stdout);
    printTestResult(MessageService::test());
    
    printf("Testing Timer");
    fflush(stdout);
    bool timerResult = Timer::test();
    printf("\t\t");
    printTestResult(timerResult);
    
    printf("Integration Test...\t\t");
    fflush(stdout);
    printTestResult(integrationTest());
    
    return 0;
}

