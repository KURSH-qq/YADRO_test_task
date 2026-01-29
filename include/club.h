#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include <memory>

#include "time_m.h"
#include "table.h"

class Club {
private:
    size_t tableCount;
    size_t busyTableCount;
    
    Time startTime;
    Time endTime;
    
    size_t price;

    std::map<std::string, size_t> clientTable;
    std::vector<Table> tables;
    std::queue<std::string> awaiting;
    const size_t NO_TABLE = 0;

    bool inClub(const std::string name);
    bool existFreeTable();

    void handleEventArrived(EventArrived& event);
    void handleEventSat(EventSat& event);
    void handleEventWaiting(EventWaiting& event);
    void handleEventLeft(EventLeft& event);

public:
    Club(const size_t tableCount, const Time& startTime, const Time& endTime, size_t price);

    void proccesEvent(Event& event);
    void endDay();
    void countMoney();
};