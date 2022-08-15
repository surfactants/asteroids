#pragma once

#include <SFML/Graphics.hpp>
#include <menu/menu_elements.hpp>
#include <system/state_hook.hpp>
#include <audio/audio_manager.hpp>
#include <vector>
#include <system/settings_package.hpp>

class Menu : public sf::Drawable, public State_Hook, public Audio_Manager{
public:
    Menu();
    void update(sf::Vector2f mpos);
    void clickLeft();
    void clickRight();
    void releaseLeft();
    void releaseRight();
    virtual void back();
    void scroll(float delta);
    virtual void saveSettings(){}
    void stopInput();

protected:
    std::vector<Option> options;
    std::map<Volume_Type, Slider> sliders;

    Main_State escape = MAIN_NULL;
    static sf::Font& font;

    std::vector<Logo> logos;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static std::vector<Nav> nav;
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

class Menu_Settings : public Menu, public Audio_Settings{
public:
    Menu_Settings();
    virtual void back() override;
    void saveSettings();
protected:
    Slider volume_music{ "music" };
    Slider volume_sound{ "sound" };
private:

    Audio_Settings audioSettings;

    void reset();

    Settings_Package generateSettingsPackage();
    void loadSettings();
};

struct Menu_Package{
    Menu_Package(Menu_Main* m, Menu_Pause* p, Menu_Settings* s)
    : m_main{ m }, m_pause{ p }, m_settings{ s }{}

    Menu_Main* m_main;
    Menu_Pause* m_pause;
    Menu_Settings* m_settings;
};
