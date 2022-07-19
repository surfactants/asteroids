#pragma once

#include <SFML/Audio.hpp>
#include <deque>
#include <map>
#include <string>

class Audio_Manager{
public:
    void playSound(sf::Sound sound);
    void playUI(sf::Sound sound);
    void update();
protected:
    static float volume_music;

    static std::deque<sf::Sound> sounds_game;
    static float volume_game;

    static float volume_ui;
    static std::deque<sf::Sound> sounds_ui;
private:

};

class Audio_Interface{
public:
    virtual void play(std::string id) = 0;
protected:
    Audio_Manager player;
    std::map<std::string, sf::SoundBuffer> sounds;
};

class Audio_Game : public Audio_Interface{
public:
    virtual void play(std::string id) override;
protected:
private:
};

class Audio_UI : public Audio_Interface{
public:
    virtual void play(std::string id) override;
protected:
private:
};

class Audio_Music : public Audio_Interface{
public:
    virtual void play(std::string id) override;
protected:
private:
};

class Audio_Settings : public Audio_Manager{
public:
    void setVolumeMusic(float nv);
    void setVolumeSound(float nv);
    void setVolumeUI(float nv);
};
