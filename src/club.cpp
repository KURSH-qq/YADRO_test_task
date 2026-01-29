#include "club.h"

Club::Club(const size_t tableCount, const Time& startTime, const Time& endTime, size_t price)
    :tableCount(tableCount), startTime(startTime), endTime(endTime), price(price)  {
    std::cout<<startTime<<'\n';
    tables.reserve(tableCount+1);
    tables.emplace_back(Table(0,0));
    for (size_t i = 1; i <= tableCount; ++i) {
        tables.emplace_back(Table(i, price));
    }
    busyTableCount = 0;
 }

bool Club::inClub(const std::string name) {
    return clientTable.contains(name);
}

bool Club::existFreeTable() {
    return !(busyTableCount == tableCount);
}

void Club::proccesEvent(Event& event) {
    switch(event.getEventId()) {
        case EventType::ARRIVED : {
            EventArrived& arrived = static_cast<EventArrived&>(event);
            handleEventArrived(arrived);
            break;
        }
        case EventType::SAT : {
            EventSat& sat = static_cast<EventSat&>(event);
            handleEventSat(sat);
            break;
        }
        case EventType::WAITING: {
            EventWaiting& waiting = static_cast<EventWaiting&>(event);
            handleEventWaiting(waiting);
            break;
        }
        case EventType::LEFT: {
            EventLeft& left = static_cast<EventLeft&>(event);
            handleEventLeft(left);
            break;
        }
        default:
            break;
    }
}

void Club::handleEventArrived(EventArrived& event) {
    event.print();
    if (inClub(event.getName())) {
        ERROR er(event.getTime(), "YouShallNotPass");
        er.print();        
    }
    else if (!Time::goodTime(event.getTime(), startTime, endTime)) {
        ERROR er(event.getTime(), "NotOpenYet");
        er.print();        
    }
    else {
        clientTable[event.getName()] = NO_TABLE;
    }
}


void Club::handleEventSat(EventSat& event) {
    event.print();
    if (!inClub(event.getName())) {
        ERROR er(event.getTime(), "ClientUnknown");
        er.print();
        return;
    }
    else if (tables[event.getTableId()].isBusy()) {
        ERROR er(event.getTime(), "PlaceIsBusy");
        er.print();
        return;
    }

    if (clientTable[event.getName()] != NO_TABLE) {
        tables[clientTable[event.getName()]].freeOrder(event);
        clientTable[event.getName()] = event.getTableId();
        tables[clientTable[event.getName()]].busyOrder(event);
    }
    else {
        size_t tableId = event.getTableId();
        tables[tableId].busyOrder(event);
        clientTable[event.getName()] = tableId;
        busyTableCount+=1;
        if (!awaiting.empty() && event.getName() == awaiting.front()) {
            awaiting.pop();
        }
    }
}

void Club::handleEventWaiting(EventWaiting& event) {
    event.print();
    if (!inClub(event.getName())) {
        ERROR er(event.getTime(), "ClientUnknown");
        er.print();
        return;
    }
    else if (existFreeTable()) {
        ERROR er(event.getTime(), "ICanWaitNoLonger");
        er.print();
    }
    else if (awaiting.size() + 1 > tableCount) {
        EventLeftOut leftOut(event.getTime(), event.getName());
        leftOut.print();
        return;
    }
    awaiting.push(event.getName());
}

void Club::handleEventLeft(EventLeft& event) {
    event.print();
    if (!inClub(event.getName())) {
        ERROR er(event.getTime(), "ClientUnknown");
        er.print();
    }
    else {
        if (!awaiting.empty()) {
            EventSatOut satOutEvent(event.getTime(), awaiting.front(), clientTable[event.getName()]);
            satOutEvent.print();
            clientTable[awaiting.front()] = clientTable[event.getName()];
            tables[clientTable[event.getName()]].freeThenBusyOrder(event);
            awaiting.pop();
        }
        else {
            tables[clientTable[event.getName()]].freeOrder(event);
            busyTableCount-=1;
        }
        clientTable.erase(event.getName());
    }
}

void Club::endDay() {
    for (const auto& itr : clientTable) {
        if (tables[itr.second].isBusy()) {
            EventLeftOut exit(endTime, itr.first);
            tables[itr.second].freeOrder(exit);
            --busyTableCount;
            exit.print();
        }
    }
    std::cout<<endTime<<'\n';
}

void Club::countMoney() {
    for (size_t i = 1; i <= tableCount; ++i) {
        std::cout<< tables[i].getId() << " " << tables[i].getMoney() << " " << tables[i].getWorkedTime()<< '\n';
    }
}