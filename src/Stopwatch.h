#pragma once
#include <ctime>
#include <sstream>

class Stopwatch {
    private:
        time_t startT;
        time_t stopT;
    public:
        Stopwatch();
        void start();
        void stop();
        std::string timeTaken();
};