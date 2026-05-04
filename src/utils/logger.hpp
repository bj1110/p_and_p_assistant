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

    static Logger& get_logger(){
        static Logger instance(LogLevel::Info);
        return instance; 
    }
    
    void log(LogLevel loglevel, std::string_view msg, std::source_location location = std::source_location::current())const; 
    
    void changeLogLevel(const LogLevel& loglevel);
    
    #define LOG(lvl, msg) (utils::Logger::get_logger()).log(lvl, msg)
    #define LOG_INFO(msg) (utils::Logger::get_logger()).log(utils::LogLevel::Info, msg)
    #define LOG_WARN(msg) (utils::Logger::get_logger()).log(utils::LogLevel::Warn, msg)
    #define LOG_ERROR(msg) (utils::Logger::get_logger()).log(utils::LogLevel::Error, msg)
    #define LOG_DEBUG(msg) (utils::Logger::get_logger()).log(utils::LogLevel::Debug, msg)



    Logger (const Logger&) = delete; 
    Logger (Logger&&) =delete;  
    Logger& operator= (Logger&&) = delete; 
    Logger& operator= (const Logger&) = delete; 

private:
    Logger() =default;
    Logger(LogLevel loglevel);

    std::string lvl_to_string(const LogLevel& lvl)const;

    LogLevel current_log_level_;
}; 



} //namespace utils 