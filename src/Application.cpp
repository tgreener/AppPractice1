
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

void Application::run(function<void (void)> appStartFunction) {
    setRunning(true);
    
    std::thread appThread( [&]{
        appStartFunction();
        runLoop();
    });
    
    appThread.join();
}

void Application::stop() {
    setRunning(false);
    
    appSem.signal();
}

bool Application::test() {
    bool result = true;
    
    Application testApp;
    
    int a1c = 0;
    
    testApp.run([&] {
        a1c++;
        testApp.stop();
    });
    
    if(a1c != 1) {
        printf("Var a1c, expected: %d actual: %d\n", 1, a1c);
        result = false;
    }
    
    return result;
}
