#include "character.hpp"

namespace entities{

Character::Character(std::string name):m_name(std::move(name)){}

Character::Character (std::string name, std::vector<stat> stats)
:m_name(std::move(name))
{
    m_stats.reserve(stats.size());
    for(stat& stat: stats){
        if(m_stats.contains(stat.name)){
            LOG_ERROR("Stat that already exists has been inserted");
        }
        m_stats.emplace(stat.name, std::move(stat));
    }
}

bool Character::addStat(stat stat){
    if(m_stats.contains(stat.name)){
        LOG_ERROR("Stat that already exists has been added");
        return false;
    }
    m_stats.emplace(stat.name, std::move(stat));
    return true; 
}

std::string Character::getName() const{
    return m_name; 
}

} //namespace entities