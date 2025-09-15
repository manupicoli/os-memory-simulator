#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

enum class LogLevel { INFO, WARN, ERROR };

void logging(LogLevel level, const std::string &message) {
    auto now = std::chrono::system_clock::now();
    std::time_t t_now = std::chrono::system_clock::to_time_t(now);
    std::tm tm_now;

#ifdef _WIN32
    localtime_s(&tm_now, &t_now);   // windows
#else
    localtime_r(&t_now, &tm_now);   // linux/macOS
#endif

    std::string lvl;
    switch(level) {
        case LogLevel::INFO:  lvl = "INFO"; break;
        case LogLevel::WARN:  lvl = "WARN"; break;
        case LogLevel::ERROR: lvl = "ERROR"; break;
    }

    std::cout << "\n["
              << std::put_time(&tm_now, "%d-%m-%Y %H:%M:%S")
              << " " << lvl << "] "
              << message << std::endl;
}