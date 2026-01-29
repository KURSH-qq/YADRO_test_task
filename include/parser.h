#pragma once
#include <string>
#include <queue>
#include <memory>
#include <vector>

#include "event.h"
#include "time_m.h"

struct InputData {
    size_t tableCount;
    size_t price;
    Time startTime;
    Time endTime;
    std::queue<std::unique_ptr<Event>> events;
};


class Parser {
private:
    struct parsedLine {
        Time time;
        std::string name;
        EventType eventId;
        size_t tableId;
    };

    static bool isValidEventId(const int eventId);
    static bool isValidClientName(const std::string& name);
    static bool isValidTableId(const int id, const size_t tableCount);
    static bool isValidTime(const std::string& time);

    static parsedLine parseLine(const std::string& line, const size_t tableCount);
public:
    static InputData getInputData(const std::string& filename);
};