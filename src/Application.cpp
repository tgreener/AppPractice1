
#include "Application.h"


using namespace std;

Application::Application() {
    running = false;
    dataSem.signal();
}

void Application::setRunning(bool val) {
    dataSem.wait();
    
    running = val;
    
    dataSem.signal();
}

void Application::runLoop() {
    while(running) {    
        // Do things like handle inputs, OS signals, etc.

        appSem.wait();
    }
}

void Application::run() {
    appThread = thread( [&] {
        runLoop();
    });
}

void Application::run(function<void (void)> appStartFunction) {
    setRunning(true);
    
    appThread = thread( [&]{
        appStartFunction();
        runLoop();
    });
}

void Application::stop() {
    setRunning(false);
    
    appSem.signal();
    appThread.join();
}

bool Application::test() {
    printf("Testing Application...\n");
    bool result = true;
    
    Application testApp;
    testApp.run();
    testApp.stop();
    
    int a1c = 0;
    
    testApp.run([&] {
        a1c++;
    });
    testApp.stop();
    
    if(a1c != 1) {
        printf("Var a1c, expected: %d actual: %d\n", 1, a1c);
        result = false;
    }
    
    return result;
}
