#include "Clock.hpp"

gg::Time::Time(){}
gg::Time::Time(double T):_Time(T){}
gg::Time::Time(const Time &orig) {
    _Time = orig._Time;
}
gg::Time::~Time(){}

double gg::Time::Seconds(){
    return _Time;
}

double gg::Time::Miliseconds(){
    return _Time*1000;
}


gg::Clock::Clock() {
    CLOCK = std::chrono::steady_clock::now();
}

gg::Clock::Clock(const Clock &orig) {
    CLOCK = orig.CLOCK;
}

gg::Clock::~Clock(){}

gg::Time gg::Clock::ElapsedTime(){
    std::chrono::steady_clock::time_point CURRENT = std::chrono::steady_clock::now();
    std::chrono::duration<double> Elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(CURRENT - CLOCK);

    return Time(Elapsed.count());
}

gg::Time gg::Clock::Restart(){
    std::chrono::steady_clock::time_point CURRENT = std::chrono::steady_clock::now();
    std::chrono::duration<double> Elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(CURRENT - CLOCK);

    CLOCK = CURRENT;

    return Time(Elapsed.count());
}
