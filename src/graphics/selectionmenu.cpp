#include "selectionmenu.hpp"


namespace graphics
{


SelectionMenu::SelectionMenu(std::shared_ptr<core::Settings> settings, const std::vector<std::string>& items, sf::Vector2f position, sf::Vector2f size_per_element, sf::Vector2f margin) 
:settings_(settings), position_(position), size_per_element_(size_per_element), margin_(margin){
    LOG_INFO("Initilizing Selection Menu"); 
    int elem_num=0;
    base_button_ = std::make_unique<FixedSizeButton> (settings_->font, std::string{"select"}, position, size_per_element_, [this](ButtonTemplate&){expandOptions();});
    base_button_->setShapesCornerSharpeness(300.f);
    base_button_->setButtonColor(sf::Color::White); 
    base_button_->setTextColor(sf::Color::Black); 
    selected_ = base_button_.get(); 
    sf::Vector2f exp_btn_pos = {position.x + size_per_element.x, position.y};
    sf::Vector2f exp_btn_size = {size_per_element_.y, size_per_element_.y}; 
    expand_button_ = std::make_unique<FixedSizeButton> (settings_->font, std::string{"v"}, exp_btn_pos , exp_btn_size, [this](ButtonTemplate&){expandOptions();});
    expand_button_->setButtonColor(sf::Color::White);
    expand_button_->setTextColor(sf::Color::Black);
    for(auto& item:items){
        sf::Vector2f elem_pos = {position};
        elem_pos.y += (static_cast<float>(++elem_num)* (size_per_element.y + 2.f*margin_.y) ); 
        auto btn = std::make_unique<FixedSizeButton> (settings_->font, item, elem_pos, size_per_element_ , createSelectionLambda());
        btn->setShapesCornerSharpeness(300.f); 
        btn->setButtonColor(sf::Color::White);
        btn->setTextColor(sf::Color::Black); 
        buttons_.emplace_back(std::move(btn)); 
    }
}

void SelectionMenu::handleEvent(const sf::Event& event){
    if(!isFocussed()){
        return;
    }
    bool hide_after = false;
    if(!options_hidden_){
        hide_after=true;
    }
    base_button_->handleEvent(event); 
    expand_button_->handleEvent(event);
    if(options_hidden_){
        return; 
    }
    for(auto& btn: buttons_){
        btn->handleEvent(event); 
    }
    if(hide_after && !options_hidden_ ){
        if(event.type == sf::Event::MouseButtonPressed){
            expandOptions(); 
        }
    }
}

void SelectionMenu::highlightSelection(size_t idx){
    if(idx >= buttons_.size()){
        LOG_ERROR("Access beyond entriey boundaries");
        return;
    }
    auto& btn = buttons_.at(idx);
    if(btn->getButtonColor() == sf::Color::Red){
        btn->setButtonColor(sf::Color::White);
    }else{
        btn->setButtonColor(sf::Color::Red);
    }
}

void SelectionMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    states.transform *= getTransform();
    target.draw(*base_button_);
    target.draw(*expand_button_);
    if(options_hidden_){
        return;  
    }
    for(const auto& button:  buttons_){
        target.draw(*button); 
    }
}

ButtonTemplate::ButtonCallback SelectionMenu::createSelectionLambda(){
    return [this](ButtonTemplate& btn){
        if(selected_ && &btn!=selected_){
            selected_->setButtonColor(sf::Color::White); 
        }
        btn.setButtonColor(sf::Color::Red);
        selected_ = &btn;
        base_button_ ->setString(btn.getString());
        options_hidden_ = true; 
    };
}

void SelectionMenu::expandOptions(){
    options_hidden_ = !options_hidden_;
    if(!options_hidden_){
        base_button_->setString("select");
    }
    else{
        base_button_->setString(selected_->getString());
    }
}


    
} // namespace graphics
