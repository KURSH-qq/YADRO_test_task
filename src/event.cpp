#include <memory>

#include "event.h"

Time Event::getTime() const {
    return eventTime;
}

std::string Event::getName() {
    return name;
}

EventType Event::getEventId() {
    return eventId;
}

std::unique_ptr<Event> Event::createEvent(const Time& time, const EventType id, const std::string& clientName, const size_t tableId) {
    switch (id)
    {
    case EventType::ARRIVED:
        return std::make_unique<EventArrived>(time, clientName);
    case EventType::SAT:
        return std::make_unique<EventSat>(time, clientName, tableId);
    case EventType::WAITING:
        return std::make_unique<EventWaiting>(time, clientName);
    case EventType::LEFT:
        return std::make_unique<EventLeft>(time, clientName);
    case EventType::LEFT_OUT:
        return std::make_unique<EventLeftOut>(time, clientName);
    case EventType::SAT_OUT:
        return std::make_unique<EventSatOut>(time, clientName, tableId);
    case EventType::ERROR:
        return std::make_unique<ERROR>(time, clientName);
    }
    return nullptr;
}

Event::Event(const Time& time, const EventType id, const std::string& client) {
    this->eventTime = time;
    eventId = id;
    name = client;
}

EventSat::EventSat(const Time& time, const std::string& name, const size_t tableId) {
    eventId = EventType::SAT;
    this->eventTime = time;
    this->eventId = eventId;
    this->name = name;
    this->tableId = tableId;
}

EventSatOut::EventSatOut(const Time& time, const std::string& name, const size_t tableId) {
    eventId = EventType::SAT_OUT;
    this->eventTime = time;
    this->eventId = eventId;
    this->name = name;
    this->tableId = tableId;
}

void Event::print() {
    std::cout<< eventTime.toClock() << " " << static_cast<size_t>(eventId) << " " << name << '\n';
}

void EventSat::print() {
    std::cout<< eventTime.toClock() << " " << static_cast<size_t>(eventId) << " " << name << " "<< tableId <<'\n';
}

void EventSatOut::print() {
    std::cout<< eventTime.toClock() << " " << static_cast<size_t>(eventId) << " " << name << " "<< tableId << '\n';
}
