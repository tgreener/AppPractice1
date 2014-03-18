
#include "ServiceLocator.h"

#include <thread>
#include <cassert>

__thread ServiceLocator* ServiceLocator::defaultLocator;

ServiceLocator::ServiceLocator() {}

ServiceLocator::~ServiceLocator() {
    if(messages != NULL) {
        delete messages;
    }
}

void ServiceLocator::createMessageService() {
    messages = new MessageService();
}

MessageService* ServiceLocator::locateMessageService() {
    if(messages == NULL) {
        ServiceLocator::createMessageService();
    }
    
    return messages;
}

void ServiceLocator::provideMessageService(MessageService* m) {
    if(messages != NULL) {
        delete messages;
    }
    
    messages = m;
}

Timer* ServiceLocator::locateTimerService() {
    return Timer::getTimer();
}

ServiceLocator* ServiceLocator::getDefaultLocator() {
    if(defaultLocator == NULL) {
        defaultLocator = new ServiceLocator();
    }
    
    return defaultLocator;
}

void testThread(int n, ServiceLocator* aDifferentThreadsLocator) {
    ServiceLocator* loc = ServiceLocator::getDefaultLocator();  
    ServiceLocator* loc2 = ServiceLocator::getDefaultLocator();
    Timer* timer1 = loc->locateTimerService();
    Timer* timer2 = loc2->locateTimerService();
    
    assert(loc == loc2);
    assert(loc != aDifferentThreadsLocator);
    
    assert(loc == loc2);
    assert(loc != NULL);
}

bool ServiceLocator::test() {
    bool result = true;
    
    int n = 0;
    
    ServiceLocator* loc = ServiceLocator::getDefaultLocator();
    
    std::thread thread1(testThread, ++n, loc);
    std::thread thread2(testThread, ++n, loc);
    
    thread1.join();
    thread2.join();
    
    return result;
}


