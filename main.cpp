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
    
    std::thread testThread;
    MessageService* mainThreadMessages = ServiceLocator::getDefaultLocator()->locateMessageService();
    Semaphore syncSem;
    
    auto threadFunction = [&] {
        Semaphore testSem;            
        ServiceLocator* loc = ServiceLocator::getDefaultLocator();

        MessageService* ms = loc->locateMessageService();
        
        mainThreadMessages->subscribe("timerEvent", [&](StringMap p) {
            ms->publish("superEvent", StringMap());
        });
        
        ms->subscribe("superEvent", [&](StringMap p) { 
            testSem.signal();
            result = true;
        });
        
        syncSem.signal();
        testSem.wait();

        app.stop();
    };
   
    app.run([&] {
        testThread = thread(threadFunction);
        syncSem.wait();
        
        Timer* timer = ServiceLocator::getDefaultLocator()->locateTimerService();
        timer->setInterval(500, [&]{ 
            mainThreadMessages->publish("timerEvent", StringMap());
        }, false);
    });
    testThread.join();
    
    return result;
}

/*
 * 
 */
int main(int argc, char** argv) {
    printf("Integration Test...\t\t");
    fflush(stdout);
    printTestResult(integrationTest());
    
    printf("Testing Application...\t\t");
    fflush(stdout);
    printTestResult(Application::test());
    
    printf("Testing ServiceLocator...\t");
    fflush(stdout);
    printTestResult(ServiceLocator::test());
    
    printf("Testing MessageService...\t");
    fflush(stdout);
    printTestResult(MessageService::test());
    
    printf("Testing EventQueue...\t\t");
    fflush(stdout);
    printTestResult(EventQueue::test());
    
    printf("Testing Timer");
    fflush(stdout);
    bool timerResult = Timer::test();
    printf("\t\t");
    printTestResult(timerResult);
    
    return 0;
}

