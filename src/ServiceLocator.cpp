
#include "ServiceLocator.h"

#include <thread>
#include <cassert>

__thread ServiceLocator* ServiceLocator::defaultLocator;
__thread MessageService* ServiceLocator::messages;

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
    
    MessageService* mes1 = loc->locateMessageService();
    MessageService* mes2 = loc2->locateMessageService();
    
    MessageService* mes3 = aDifferentThreadsLocator->locateMessageService();
    
    assert(loc == loc2);
    assert(loc != aDifferentThreadsLocator);
    assert(loc != NULL);
    
    assert(timer1 == timer2);
    assert(mes1 != NULL);
    assert(mes1 == mes2);
    //assert(mes1 != mes3);
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


