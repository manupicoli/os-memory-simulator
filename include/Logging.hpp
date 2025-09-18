#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string>

enum class LogLevel { INFO, WARN, ERROR, VISUAL, ACTION, ALLOC, SUCCESS, METRICS };

void logging(LogLevel level, const std::string &message);

#endif
