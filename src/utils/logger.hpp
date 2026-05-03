#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <source_location>
#include <string_view>


namespace utils{

enum LogLevel {Debug, Info, Warn, Error};

class Logger{
public: 
    Logger(LogLevel loglevel); 

    void log(std::string_view msg, std::source_location location = std::source_location::current())const; 

    void changeLogLevel(const LogLevel& loglevel);

    #define LOG(logger, msg) (logger).log(msg)
    
private:
    std::string lvl_to_string(const LogLevel& lvl)const;
    LogLevel loglevel_; 

}; 



} //namespace utils 