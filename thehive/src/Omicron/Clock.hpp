#ifndef _TIME_CLOCK_H
#define _TIME_CLOCK_H


#include <chrono>

namespace gg{

    class Time {
        public:
            Time();
            Time(double T);
            Time(const Time &orig);
            ~Time();

            double Seconds();
            double Miliseconds();

        private:
            double _Time;
    };


    class Clock {
        public:
            Clock();
            Clock(const Clock &orig);
            ~Clock();

            Time ElapsedTime();
            Time Restart();

        private:
            std::chrono::steady_clock::time_point CLOCK;
    };
    
};

#endif
