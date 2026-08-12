#include "gameboard.hpp"

namespace core
{

Gameboard::Gameboard(std::shared_ptr<Settings> settings, std::shared_ptr<graphics::GUI_manager> gui_manager) 
: m_settings(settings), m_gui_manager(gui_manager){}


void Gameboard::init(u_int num_players, const std::vector<u_int>& dice){
    LOG_INFO("Initializing Gameboard ..."); 
    m_num_players = num_players;
    for(u_int w: dice){
        mechanics::Dice d {w};
        m_dice.insert({w, d}); 
    }
    LOG_INFO("Gameboard initialized."); 

    std::vector<graphics::InputPopUp::InputType> fields{
        {std::string{"Stat1"}, graphics::Textfield::Type::String},
        {std::string{"Stat2"}, graphics::Textfield::Type::String},
        {std::string{"Stat3"}, graphics::Textfield::Type::String},
        {std::string{"Stat4"}, graphics::Textfield::Type::String},
        {std::string{"Stat5"}, graphics::Textfield::Type::String},
    };
    std::shared_ptr<graphics::InputPopUp> inputPopUp = std::make_shared<graphics::InputPopUp>(
        m_settings, 
        sf::Vector2f{300.f, 500.f},
        "Add Default Stats",
        fields,
        [this, fields](const graphics::InputResult& result){
            for(const auto& field: fields){
                std::string stat = std::get<std::string>(result.at(field.fieldname));
                if(stat==""){
                    continue;
                }
                m_stats.insert(stat);
                LOG_INFO(std::format("Added new Stat: {}", stat)); 
            }
            std::shared_ptr<graphics::ResizingButton> create_player_btn = std::make_shared<graphics::ResizingButton>(
                m_settings->font,
                "Create new\n Character",
                sf::Vector2f{0.f, 0.f},
                [this](graphics::ButtonTemplate&){
                    create_character(); 
                }
            );
            create_player_btn->setButtonColor(sf::Color(120, 150, 90));

            if(!m_gui_manager->addElement(create_player_btn)){
                LOG_WARN("Couldn't create Button for player creation");
            }
            m_gui_manager->focusElement(create_player_btn.get());
        }
    );
    if(!m_gui_manager->addElement(inputPopUp)){
        LOG_WARN("Element was not added "); 
    }
    m_gui_manager->focusElement(inputPopUp.get());


}

int Gameboard::roll_dice(u_int sides){
    if(!m_dice.contains(sides)){
        LOG_WARN(std::format("There is no dice with {} amount of sides.", sides));
        return -1;
    }
    int n = m_dice.at(sides).roll();
    LOG_DEBUG(std::format("Rolled {}", n)); 
    return n; 
}

const std::unordered_map<u_int, mechanics::Dice> Gameboard::getAllDice() const{
    return m_dice; 
}


bool Gameboard::add_character(std::shared_ptr<entities::Character> character){
    std::string name= character->getName();
    if(m_characters.contains(name)){
        LOG_ERROR("Trying to add Character that already exists");
        return false;
    }
    m_characters.emplace(character->getName(), std::move(character)); 
    return true; 
} 

std::shared_ptr<entities::Character> Gameboard::getCharater(const std::string& name){
    if(m_characters.contains(name)){
        return m_characters[name];
    }
    return nullptr;
}

void Gameboard::create_character(){
    std::vector<graphics::InputPopUp::InputType> fields;

    fields.push_back({"Name", graphics::Textfield::Type::String});

    for(const std::string& stat: m_stats){
        graphics::InputPopUp::InputType input {stat, graphics::Textfield::Type::Int};
        fields.push_back(input);
    }
    std::shared_ptr<graphics::InputPopUp> inputPopUp = std::make_shared<graphics::InputPopUp>(
        m_settings, 
        sf::Vector2f{300.f, 500.f},
        "Add new Character",
        fields,
        [this, fields](const graphics::InputResult& result){
            std::string name = std::get<std::string>(result.at("Name"));
            std::vector<entities::Character::stat> stats;
            for(const auto& field: fields){
                if(field.fieldname == "Name")
                        continue;
                int stat_value = std::get<int>(result.at(field.fieldname));
                if(stat_value==-1){
                    LOG_WARN(std::format("Stat {}, has not been given an max value for character {}. Setting To 0", field.fieldname, name));
                }
                stats.push_back({field.fieldname, stat_value, stat_value});
            }
            std::shared_ptr<entities::Character> character = std::make_shared<entities::Character>(name, stats);
            if(add_character(character)){
                LOG_INFO(std::format("Successfully added new character {}", name));
            }else{
                LOG_ERROR("Failed to add new character"); 
            }
        }
    );
    if(!m_gui_manager->addElement(inputPopUp)){
        LOG_WARN("Element was not added "); 
    }




}




} // namespace core
