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
#include <functional>
#include "MessageListener.h"

typedef std::unordered_map<std::string, std::string> StringMap;
typedef std::function<void (StringMap)> Callback;
typedef std::unordered_map<std::string, std::vector<Callback>> SubscriptionMap;
typedef std::vector<Callback> CallbackList;

class MessageService {
private:
     SubscriptionMap subscriptions;
    
public:
    MessageService();
    ~MessageService();
    
    void subscribe(std::string message, Callback callback);
    void publish(std::string message, StringMap params);
    
    static bool test();
};

#endif	/* MESSAGESERVICE_H */

