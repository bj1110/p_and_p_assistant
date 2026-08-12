#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "utils/logger.hpp"


namespace entities{


class Character{
public:
    struct stat{
        std::string name {"Default Stat"};
        int max_value =0;
        int curr_value =0;
    };


    Character(std::string name);
    Character(std::string name, std::vector<stat> stats);
    bool addStat(stat stat);
    std::string getName()const;

private:
    std::string m_name = "Default Character Name";
    std::unordered_map<std::string, stat> m_stats {};

};


} //namespace entities