#include "logger.hpp"

namespace utils{

Logger::Logger(LogLevel loglevel): loglevel_(loglevel) {}


void Logger::log(std::string_view msg, std::source_location location)const{
    std::cout << lvl_to_string(loglevel_); 
    if(loglevel_ == Debug){
        std::cout 
        << location.file_name() <<": " 
        << location.function_name() <<": "
        << "ll "<< location.line() <<": ";
    }
    std::cout << msg <<std::endl;
}

void Logger::changeLogLevel(const LogLevel& loglevel){
    loglevel_=loglevel; 
}


std::string Logger::lvl_to_string(const LogLevel& lvl) const{
    std::string name;
    switch (lvl){
        case Debug: name="Debug";
            break;
        case Info: name="Info";
            break;
        case Warn: name="Warn";
            break;
        case Error: name="Error";
            break;
        default: name="unknown";
    }
    return "[" + name +"] ";
}

} //namespace utils 