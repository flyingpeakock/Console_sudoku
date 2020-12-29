#include "Stopwatch.h"

Stopwatch::Stopwatch() {
    startT = 0;
    stopT = 0;
}

void Stopwatch::start() {
    startT = time(NULL);
}

void Stopwatch::stop() {
    if (startT == 0) {
        return;
    }
    stopT = time(NULL);
}

std::string Stopwatch::timeTaken() {
    if (stopT == 0) {
        return "Stopwatch not stopped";
    }

    time_t totalTime = stopT - startT;
    std::ostringstream timeStr;

    int hours = totalTime / (60 * 60);
    int minutes = (totalTime - (hours * 60 * 60)) / 60;
    int seconds = totalTime - (hours * 60 * 60) - (minutes * 60);

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