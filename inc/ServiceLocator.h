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
    MessageService* messages;
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
    
    Timer* locateTimerService();
    
    /*
     * Tell the locator which message service object to use. Any previous 
     * message object is deleted;
     */
    void provideMessageService(MessageService* m);
    
    static ServiceLocator* getDefaultLocator();
    static bool test();
};

#endif	/* SERVICELOCATOR_H */

