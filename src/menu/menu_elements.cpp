#include <menu/menu_elements.hpp>
#include <util/url.hpp>
#include <resources/texture_manager.hpp>

Nav::Nav(std::string nlabel, sf::Font& font, Main_State ntmain, Menu_State ntmenu)
: Button{ nlabel, font }{
    target_main = ntmain;
    target_menu = ntmenu;
}

Target::Target(std::function<void()> nt)
: target{ nt }{}

Target_With_String::Target_With_String(std::function<void(std::string)> nt)
: target{ nt }{}

Option::Option(std::string nlabel, sf::Font& font, std::function<void()> nt)
: Button{ nlabel, font }, Target(nt){}

Logo::Logo(std::string nurl, sf::Vector2f pos, std::string key)
: url{ nurl }{
    logo.setTexture(Texture_Manager::get(key));
    logo.setOrigin(sf::Vector2f((logo.getGlobalBounds().left + logo.getGlobalBounds().width) / 2.f, (logo.getGlobalBounds().top + logo.getGlobalBounds().height) / 2.f));
    logo.setPosition(pos);
    shadow.setTexture(Texture_Manager::get(std::string(key + "-SHADOW")));
    shadow.setOrigin(sf::Vector2f((shadow.getGlobalBounds().left + shadow.getGlobalBounds().width) / 2.f, (shadow.getGlobalBounds().top + shadow.getGlobalBounds().height) / 2.f));
    shadow.setPosition(pos);
}

void Logo::update(sf::Vector2f& mpos){
    bool contains = shadow.getGlobalBounds().contains(mpos);
    if(!highlighted && contains){
        highlight();
    }
    else if(highlighted && !contains){
        unhighlight();
    }
}

bool Logo::click(){
    if(highlighted){
        launchURL(url);
    }

    return highlighted;
}

void Logo::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(highlighted) target.draw(shadow, states);
    target.draw(logo, states);
}

bool Logo::isHighlighted(){
    return highlighted;
}

void Logo::highlight(){
    highlighted = true;
}

void Logo::unhighlight(){
    highlighted = false;
}
