/* 
 * File:   ServiceLocator.h
 * Author: toddgreener
 *
 * Created on March 10, 2014, 3:40 PM
 */

#ifndef SERVICELOCATOR_H
#define	SERVICELOCATOR_H

#include "MessageService.h"
#include "Timer.h"

class ServiceLocator {
private:
    static __thread MessageService* messages;
    static __thread ServiceLocator* defaultLocator;
    
    /*
     * Use to create a message service object if the message service is null;
     */    
    void createMessageService();
    ServiceLocator();
    ~ServiceLocator();
    
public:
    /*
     * This method returns the global message service object. If no message
     * service object has been specified, one is created.
     */
    MessageService* locateMessageService();
    
    /*
     * Get the timer service object.
     */
    Timer* locateTimerService();
    
    /*
     * Get the service locator for this thread. 
     */    
    static ServiceLocator* getDefaultLocator();
    
    static bool test();
};

#endif	/* SERVICELOCATOR_H */

