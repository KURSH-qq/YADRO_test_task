#include <iostream>

#include "table.h"

Table::Table(const size_t id, const size_t price): id(id), price(price) {
    busy = false;
    money = 0;
}

void Table::busyOrder(const Event& event) {
    busy = true;
    lastOrderTime = event.getTime();
}

void Table::freeOrder(const Event& event) {
    Time minutes(event.getTime() - lastOrderTime);
    workedTime += minutes;
    if (minutes % 60 != 0){
        money += ((minutes / 60) + 1) * price;
    }
    else {
        money += (minutes / 60) * price;
    }
    busy = false;
}

void Table::freeThenBusyOrder(const Event& event) {
    this->freeOrder(event);
    this->busyOrder(event);
}

size_t Table::getId() {
    return id;
}

Time Table::getWorkedTime() {
    return workedTime;
}

size_t Table::getMoney() {
    return money;
}

bool Table::isBusy() {
    return busy;
}