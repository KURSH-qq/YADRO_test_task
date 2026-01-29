#pragma once
#include <iostream>

#include "event.h"
#include "time_m.h"

class Table {
private:
    size_t id;
    size_t money;
    size_t price;
    
    bool busy;

    Time workedTime{};
    Time lastOrderTime{};
public:
    Table();
    Table(const size_t id, const size_t price);
    void busyOrder(const Event& event);
    void freeOrder(const Event& event);
    void freeThenBusyOrder(const Event& event);

    bool isBusy();

    size_t getId();
    size_t getMoney();
    Time getWorkedTime();
};