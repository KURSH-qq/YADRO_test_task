#pragma once
#include <iostream>
#include <string>

class Time {
private:
    size_t timeInMinutes;
    std::string time;
    std::string minutesToStr(const size_t minutes);
public:
    Time();
    Time(const std::string& time);
    Time(const size_t timeInMinutes);
    static bool goodTime(const Time& time, const Time& startTime, const Time& endTime);

    size_t getMinutes() const;
    std::string toClock() const;

    Time operator-(const Time& time) const;
    Time& operator+=(const Time& time);
    size_t operator/(const int scal) const;
    size_t operator%(const int scal) const;

    bool operator<=(const Time& time) const;

    Time& operator=(const Time& time);

    friend std::ostream& operator<<(std::ostream& os, const Time& time);
    
    Time(const Time&) = default;
    Time(Time&&) = default;
    Time& operator=(Time&& time) = default;
    ~Time() = default;
};