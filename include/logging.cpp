#include "Logging.hpp"
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

using namespace std;

void logging(LogLevel level, const string &message) {
    auto now = chrono::system_clock::now();
    time_t t_now = chrono::system_clock::to_time_t(now);
    tm tm_now;
#ifdef _WIN32
    localtime_s(&tm_now, &t_now);
#else
    localtime_r(&t_now, &tm_now);
#endif

    string lvl;
    switch (level) {
        case LogLevel::INFO:  lvl = "INFO"; break;
        case LogLevel::WARN:  lvl = "WARN"; break;
        case LogLevel::ERROR: lvl = "ERROR"; break;
    }

    cout << "["
              << put_time(&tm_now, "%d-%m-%Y %H:%M:%S")
              << " " << lvl << "] "
              << message << endl;
}