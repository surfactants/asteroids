#pragma once

#include <SFML/Audio.hpp>
#include <deque>

class Audio_Manager{
public:
    void playSound();
    void playUI();
    void update();
protected:
private:
    static float volume_music;

    static std::vector<sf::Sound> sounds_game;
        static float volume_sound;
        sf::SoundBuffer s_whatever; //holds sound data to be passed into sounds

    static std::vector<sf::Sound> sounds_ui;
        static float volume_ui;
};

class Audio_Interface{
public:
protected:
    Audio_Manager player;
private:
};

class Audio_Game_Interface : public Audio_Interface{
public:
protected:
private:
};

class Audio_UI_Interface : public Audio_Interface{
public:
protected:
private:
};

class Audio_Music_Interface : public Audio_Interface{
public:
protected:
private:
};

class Audio_Settings : public Audio_Manager{
public:
    void setVolumeMusic(float nv);
    void setVolumeSound(float nv);
    void setVolumeUI(float nv);
};
