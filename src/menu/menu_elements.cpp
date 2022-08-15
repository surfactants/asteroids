#include <menu/menu_elements.hpp>
#include <util/url.hpp>

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

Logo::Logo(std::string nurl, sf::Vector2f pos)
: url{ nurl }{
    texture_logo.loadFromFile("sfml-icon-small.png");
    texture_shadow.loadFromFile("sfml-logo-small.png");

    logo.setTexture(texture_logo);
    logo.setPosition(pos);
    shadow.setTexture(texture_shadow);
    shadow.setPosition(pos);
}

void Logo::update(sf::Vector2f& mpos){
    bool contains = logo.getGlobalBounds().contains(mpos);
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
