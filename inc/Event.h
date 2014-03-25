/* 
 * File:   EVent.h
 * Author: toddgreener
 *
 * Created on March 19, 2014, 2:27 PM
 */

#ifndef EVENT_H
#define	EVENT_H

#include <string>

class Event {
private:
    std::string eventDescription;
public:
    Event(std::string descpription);
    std::string getDescription();
};

#endif	/* EVENT_H */

