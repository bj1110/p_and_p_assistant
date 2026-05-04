#include "logger.hpp"

namespace utils{

Logger::Logger(LogLevel loglevel): current_log_level_(loglevel) {}


void Logger::log(LogLevel loglevel, std::string_view msg, std::source_location location)const{
    if(loglevel<current_log_level_){
        return; 
    }
    std::cout << lvl_to_string(loglevel); 
    if(loglevel != LogLevel::Info){
        std::cout 
        << location.file_name() <<"("<< "line "<< location.line() <<"): "
        << "'" << location.function_name() <<"': "; 
    }
    std::cout << msg <<std::endl;
}

void Logger::changeLogLevel(const LogLevel& loglevel){
    current_log_level_=loglevel; 
}


std::string Logger::lvl_to_string(const LogLevel& lvl) const{
    std::string name;
    switch (lvl){
        case Debug: name="\033[0m[DEBUG] ";
            break;
        case Info: name="\033[0m[INFO] ";
            break;
        case Warn: name="\033[35m[WARN] ";
            break;
        case Error: name="\033[31m[ERROR] ";
            break;
        default: name="unknown";
    }
    return name;
}

} //namespace utils 