
#include "Event.h"

Event::Event(std::string description) : eventDescription(description) {}

std::string Event::getDescription() {
    return eventDescription;
}
