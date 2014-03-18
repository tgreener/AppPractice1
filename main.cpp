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
        printf("Test Successful!\n");
    }
    else {
        printf("Test Failed!\n");
    }
}

bool integrationTest() {
    printf("Integration Test...\n");
    
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
    printTestResult(Application::test());
    ServiceLocator::test();
    printTestResult(Timer::test());
    printTestResult(integrationTest());
    
    return 0;
}

