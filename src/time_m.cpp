#include "time_m.h"

Time::Time() {
    time.clear();
    timeInMinutes = 0;
}

Time::Time(const std::string& time) : time(time){
    timeInMinutes = std::stoul(time.substr(0,2))*60 + std::stoul(time.substr(3,2));
}

size_t Time::getMinutes() const {
    return timeInMinutes;
}

bool Time::operator<=(const Time& time) const {
    return this->timeInMinutes <= time.timeInMinutes;
}

std::string Time::toClock() const {
    return time;
}

bool Time::goodTime(const Time& time, const Time& startTime, const Time& endTime) {
    if (startTime <= time && time <= endTime) {
        return true;
    }
    return false;
}

size_t Time::operator/(const int scal) const {
    if (scal == 0) {
        throw std::runtime_error("division by zero");
    }
    else if (scal < 0) {
        throw std::runtime_error("Time can't be negative");
    }
    return this->timeInMinutes / scal;
}

std::string Time::minutesToStr(const size_t minutes) {
    std::string result{};
        if (minutes / 60 < 10) {
        result += "0";
    }
    result += std::to_string(minutes / 60) + ":" ;
    if (minutes % 60 < 10) {
        result+= "0";
    }
    result += std::to_string(minutes % 60);
    return result;
}

Time::Time(const size_t timeInMinutes) : timeInMinutes(timeInMinutes) {
    time.clear();
    time = minutesToStr(timeInMinutes);
}

Time Time::operator-(const Time& time) const {
    Time result(this->timeInMinutes - time.timeInMinutes);
    return result;
}

Time& Time::operator+=(const Time& t){
    timeInMinutes += t.timeInMinutes;
    time = minutesToStr(timeInMinutes);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Time& time) {
    return os << time.toClock();
}


Time& Time::operator=(const Time& time) {
    this->time = time.time;
    this->timeInMinutes = time.timeInMinutes;
    return *this;
}

size_t Time::operator%(const int scal) const {
    if (scal == 0) {
        throw std::runtime_error("division by zero");
    }
    else if (scal < 0) {
        throw std::runtime_error("Time can't be negative");
    }
    return this->timeInMinutes % scal;
}