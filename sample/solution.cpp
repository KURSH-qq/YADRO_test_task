#include <iostream>
#include <string>
#include <memory>

#include "parser.h"
#include "club.h"

int main(int argc, char* argv[]) {
    if (argc != 2 ) {
        throw std::invalid_argument("bad input");
    }
    std::string fileName = argv[1];
    InputData data = Parser::getInputData(fileName);
    Club club(data.tableCount, data.startTime, data.endTime, data.price);
    while (!data.events.empty()) {
        Event* event = data.events.front().get();
        club.proccesEvent(*event);
        data.events.pop();
    }
    club.endDay();
    club.countMoney();
}