#include <fstream>
#include <queue>
#include <unordered_set>

#include "parser.h"
#include "event.h"

InputData Parser::getInputData(const std::string& fileName) {
    std::ifstream in(fileName);
    if (!in.is_open()) {
        throw std::runtime_error("Can't open " + fileName);
    }
    InputData data;
    try {
        int tableCount = 0;
        int price = 0;

        std::string cur;
        if (!std::getline(in, cur)) {
            throw std::invalid_argument("file is empty");
        }
        tableCount = std::stoi(cur);
        if (tableCount <= 0) {
            std::cout<<cur<<'\n';
            throw std::invalid_argument("negative table count");
        }

        if (!std::getline(in, cur)) {
            throw std::invalid_argument("missing working time");
        }
        size_t spaceIndex = cur.find(' ');
        Time startTime, endTime;
        if (isValidTime(cur.substr(0, 5)) && isValidTime(cur.substr(spaceIndex + 1, 5))) {
            startTime = Time(cur.substr(0, 5));
            endTime = Time(cur.substr(spaceIndex + 1, 5));
        }
        else {
            std::cout<<cur<<'\n';
            throw std::invalid_argument("invalid time");
        }

        if (!std::getline(in, cur)) {
            throw std::invalid_argument("missing price");
        }
        price = std::stoi(cur);
        if (price <= 0) {
            std::cout<<cur<<'\n';
            throw std::invalid_argument("price must be positive");
        }
        std::queue<std::unique_ptr<Event>> events;

        while (std::getline(in, cur)) {
            parsedLine line = parseLine(cur, tableCount);
            events.push(std::move(Event::createEvent(line.time, line.eventId, line.name, line.tableId)));
        }
        data.endTime = endTime;
        data.startTime = startTime;
        data.price = price;
        data.tableCount = tableCount;
        data.events = std::move(events);
        in.close();
    } catch (const std::exception& e) {
        throw std::invalid_argument("invalid line");
    }
    return data;
}

Parser::parsedLine Parser::parseLine(const std::string& line, const size_t tableCount) {
    std::vector<size_t> poses;
    parsedLine result;
    poses.push_back(line.find(' ', 0));
    while (line.find(' ', poses.back() + 1) != std::string::npos) {
        poses.push_back(line.find(' ', poses.back() + 1));
    }
    if (poses.size() == 2 || poses.size() == 3) {
        std::string time = line.substr(0, poses[0]);
        int id = std::stoi(line.substr(poses[0] + 1, poses[1] - poses[0] - 1));
        std::string name;
        int tableId = 0;

        if (poses.size() == 2) {
            name = line.substr(poses[1] + 1, line.size() - poses[1] - 1);
        }
        else {
            name = line.substr(poses[1] + 1, poses[2] - poses[1] - 1);
            tableId = std::stoi(line.substr(poses[2] + 1, line.size() - poses[2] - 1));
        }

        if (isValidTime(time)) {
            result.time = Time(time);
        }
        else {
            std::cout<<line<<'\n';
            throw std::invalid_argument("invalid time");
        }

        if (isValidClientName(name)) {
            result.name = name;
        }
        else {
            std::cout<<line<<'\n';
            throw std::invalid_argument("invalid name");
        }

        if (isValidTableId(tableId,tableCount)) {
            result.tableId = tableId;
        }
        else {
            std::cout<<line<<'\n';
            throw std::invalid_argument("invalide table ID");
        }

        if (isValidEventId(id)) {
            result.eventId = static_cast<EventType>(id);
        }
        else {
            std::cout<<line<<'\n';
            throw std::invalid_argument("invalid event type");
        }
    }
    else {
        std::cout<<line<<'\n';
        throw std::invalid_argument("invalid input");
    }
    return result;
}

bool Parser::isValidEventId(const int eventId) {
    const std::unordered_set<int> validVlaues = {1,2,3,4,11,12,13};
    if (validVlaues.contains(eventId)) {
        return true;
    }
    return false;
}

bool Parser::isValidClientName(const std::string& name) {
    if (name.substr(0,6) != "client") {
        return false;
    }
    else if (std::stoi(name.substr(6, name.size()-6)) <=0) {
        return false;
    }
    return true;
}

bool Parser::isValidTableId(const int id, const size_t tableCount) {
    if (id < 0 || static_cast<size_t>(id) > tableCount) {
        return false;
    }
    return true;
}

bool Parser::isValidTime(const std::string& time) {
    std::string hour = time.substr(0,2);
    std::string minutes = time.substr(3,2);

    if (time[2] != ':') {
        return false;
    }
    else if (std::stoi(hour) > 23 || std::stoi(hour) < 0) {
        return false;
    }
    else if (std::stoi(minutes) > 59 || std::stoi(minutes) < 0) {
        return false;
    }
    return true;
}