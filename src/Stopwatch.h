#pragma once
// #include <ctime>
#include <thread>
#include <sstream>

class Stopwatch {
    private:
        static bool running;
        static std::thread counter;
        static int seconds;
        static int minutes;
        static int hours;
    public:
        static void count();
        Stopwatch();
        void start();
        void stop();
        std::string timeTaken();
};