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
        Timer* timer = Timer::getTimer();
        timer->setInterval(250, [&]{ result = true; }, false);
        timer->setInterval(510, [&]{ app.stop(); }, false);
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

