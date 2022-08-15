#pragma once

#include <ui/button.hpp>
#include <ui/slider.hpp>
#include <system/state.hpp>

struct Nav : public Button{
    Nav(std::string nlabel, sf::Font& font, Main_State ntmain, Menu_State ntmenu);
    Main_State target_main;
    Menu_State target_menu;
};

struct Target{
    Target(){}
    Target(std::function<void()> nt);

    std::function<void()> target;
};

struct Target_With_String{ //oh god this is terrible, FIX THIS
    Target_With_String(){}
    Target_With_String(std::function<void(std::string)> nt);

    std::function<void(std::string)> target;
};

struct Option : public Button, public Target{
    Option(std::string nlabel, sf::Font& font, std::function<void()> nt);
};

class Logo : public sf::Drawable{
public:
    Logo(){}
    Logo(std::string nurl, sf::Vector2f pos);

    bool isHighlighted();
    void highlight();
    void unhighlight();
    void update(sf::Vector2f& mpos);

    bool click();

private:
    std::string url;

    sf::Sprite logo;
    sf::Sprite shadow;

    sf::Texture texture_logo;
    sf::Texture texture_shadow;

    bool highlighted;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
