#include "Stopwatch.h"
#include <chrono>

bool Stopwatch::running = false;
std::thread Stopwatch::counter;
int Stopwatch::seconds = 0;
int Stopwatch::minutes = 0;
int Stopwatch::hours = 0;

Stopwatch::Stopwatch(){
}

void Stopwatch::start() {
    if (running) {
        return;
    }
    running = true;
    counter = std::thread(&count);
}

void Stopwatch::stop() {
    running = false;
    counter.join();
}

void Stopwatch::count() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (seconds == 60) {
            seconds = 0;
            minutes++;
        }
        else if (minutes == 60) {
            minutes = 0;
            hours++;
        }
        else {
            seconds++;
        }
    }
}

std::string Stopwatch::timeTaken() {
    std::ostringstream timeStr;

    timeStr << "Time taken: ";
    if (hours > 1) {
        timeStr << hours << " Hours ";
    }
    else if (hours == 1) {
        timeStr << hours << " Hour ";
    }
    if (minutes > 1) {
        timeStr << minutes << " Minutes ";
    }
    else if (minutes == 1) {
        timeStr << minutes << " Minute ";
    }
    if (seconds > 1 || seconds == 0) {
        timeStr << seconds << " Seconds";
    }
    else if (seconds == 1) {
        timeStr << seconds << " Second";
    }
    return timeStr.str();
}