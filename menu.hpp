#pragma once

#include <SFML/Graphics.hpp>
#include "menu_elements.hpp"
#include "state_hook.hpp"
#include "audio_manager.hpp"

class Menu : public sf::Drawable, public State_Hook{
public:
    Menu();
protected:
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Menu_Main : public Menu{
public:
    Menu_Main();
protected:
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Menu_Pause : public Menu{
public:
    Menu_Pause();
protected:
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Menu_Settings : public Menu{
public:
    Menu_Settings();
protected:
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Slider volume_music{ "music" };
    Slider volume_sound{ "sound" };

    Audio_Settings audioSettings;
};;
