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

/*
 * 
 */
int main(int argc, char** argv) {
    printTestResult(Application::test());
    ServiceLocator::test();
    printTestResult(Timer::test());
    
    return 0;
}

