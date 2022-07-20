#pragma once

#include <SFML/Graphics.hpp>
#include "menu_elements.hpp"
#include "state_hook.hpp"
#include "audio_manager.hpp"
#include <vector>

struct Nav : public Button{
    Nav(std::string nlabel, sf::Font& font, Main_State ntmain, Menu_State ntmenu);
    Main_State target_main;
    Menu_State target_menu;
};

class Menu : public sf::Drawable, public State_Hook{
public:
    Menu();
    void update(sf::Vector2f mpos);
    void clickLeft();
    void clickRight();
    void releaseLeft();
    void releaseRight();

protected:
    std::map<std::string, Button> options;
    std::map<std::string, Slider> sliders;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static std::vector<Nav> nav;
    static sf::Font font;
};

class Menu_Main : public Menu{
public:
    Menu_Main();
protected:
private:
};

class Menu_Pause : public Menu{
public:
    Menu_Pause();
protected:
private:
};

class Menu_Settings : public Menu{
public:
    Menu_Settings();
protected:
    Slider volume_music{ "music" };
    Slider volume_sound{ "sound" };
private:

    Audio_Settings audioSettings;
};

struct Menu_Package{
    Menu_Package(Menu_Main* m, Menu_Pause* p, Menu_Settings* s)
    : m_main{ m }, m_pause{ p }, m_settings{ s }{}

    Menu_Main* m_main;
    Menu_Pause* m_pause;
    Menu_Settings* m_settings;
};
