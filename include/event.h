#pragma once
#include <string>
#include <memory>

#include "time_m.h"

enum class EventType: size_t {
    ARRIVED = 1,
    SAT = 2,
    WAITING = 3,
    LEFT = 4,
    LEFT_OUT = 11,
    SAT_OUT = 12,
    ERROR = 13
};

class Event {
protected:
    std::string name;
    Time eventTime;
    EventType eventId;
    Event(){}
public:
    Event(const Time& time, const EventType id, const std::string& client);
    static std::unique_ptr<Event> createEvent(const Time& time, const EventType id, const std::string& clientName, const size_t tableId = 0);
    
    Time getTime() const;
    std::string getName();
    EventType getEventId();

    virtual void print();
};

class EventArrived: public Event {
public:
    EventArrived(const Time& time, const std::string& name) : Event(time, EventType::ARRIVED, name) {}
};

class EventSat: public Event {
private:
    size_t tableId;
public:
    EventSat(const Time& time, const std::string& name, const size_t tableId);

    size_t getTableId() {
        return tableId;
    }
    void print() override;
};

class EventWaiting: public Event {
public:
    EventWaiting(const Time& time, const std::string& name) : Event(time, EventType::WAITING, name) {}
};

class EventLeft: public Event {
public:
    EventLeft(const Time& time, const std::string& name) : Event(time, EventType::LEFT, name) {}
};

class EventLeftOut: public Event {
public:
    EventLeftOut(const Time& time,const std::string& name) : Event(time, EventType::LEFT_OUT, name) {}
};

class EventSatOut: public Event {
private:
    size_t tableId;
public:
    EventSatOut(const Time& time, const std::string& name, const size_t tableId);
    void print() override;
};

class ERROR : public Event {
public:
    ERROR(const Time& time, const std::string& name) : Event(time, EventType::ERROR, name) {}
};