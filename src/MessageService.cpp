
#include "MessageService.h"

using namespace std;

MessageService::MessageService() {
}

MessageService::~MessageService() {
}
    
void MessageService::subscribe(std::string message, Callback callback) {
    SubscriptionMap::const_iterator got = subscriptions.find(message);
    
    fflush(stdout);
    
    if(got == subscriptions.end()) {
        CallbackList newList;
        newList.push_back(callback);
        
        subscriptions.insert({message, newList});
    }
    else {
        CallbackList messageList = got->second;
        messageList.push_back(callback);
    }
}

void MessageService::publish(std::string message, StringMap params) {
    fflush(stdout);
    SubscriptionMap::const_iterator got = subscriptions.find(message);
    
    if(got != subscriptions.end()) {
        fflush(stdout);
        CallbackList messageList = got->second;
        
        for(CallbackList::size_type i = 0; i < messageList.size(); i++) {
            fflush(stdout);
            messageList[i](params);
        }
    }
}

bool MessageService::test() {
    MessageService messages;
    
    bool result = true;
    
    int messageTestA = 0;
    std::string testBString;
    
    messages.subscribe("testA", [&](StringMap p){messageTestA++;});
    messages.subscribe("testB", [&](StringMap p){testBString = p.find("a")->second;});
    
    StringMap emptyParams;
    StringMap testBParams;
    
    testBParams.insert({"a", "paramA"});
    
    messages.publish("testA", emptyParams);
    messages.publish("testB", testBParams);
    messages.publish("testC", emptyParams);
    
    if(messageTestA != 1) {
        printf("Var messageTestA, expected: %d actual: %d\n", 1, messageTestA);
        result = false;
    }
    
    if(testBString.compare("paramA") != 0) {
        printf("Var testBString, expected: %s actual: %s\n", "paramA", testBString.c_str());
        result = false;
    }
    
    return result;
}
