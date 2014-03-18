/* 
 * File:   MessageService.h
 * Author: toddgreener
 *
 * Created on March 10, 2014, 3:48 PM
 */

#ifndef MESSAGESERVICE_H
#define	MESSAGESERVICE_H

#include <unordered_map>
#include <vector>
#include <string>
#include "MessageListener.h"

class MessageService {
private:
    std::unordered_map<std::string, std::vector<MessageListener*> > subscriptions;
    
public:
    MessageService();
    ~MessageService();
    
    void subscribe(std::string message, MessageListener* listener);
    void publishMessage(std::string message, std::unordered_map<std::string, std::string> params);
};

#endif	/* MESSAGESERVICE_H */

