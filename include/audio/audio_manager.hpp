#pragma once

#include <SFML/Audio.hpp>
#include <audio/audio_bus.hpp>
#include <deque>
#include <map>
#include <string>

class Audio_Manager : public Audio_Bus{
public:
    void playSound(sf::Sound sound);
    void playUI(sf::Sound sound);
    void update();
protected:
    static float volume_music;
    static sf::Music music;

    static std::deque<sf::Sound> sounds_game;
    static float volume_game;

    static float volume_ui;
    static std::deque<sf::Sound> sounds_ui;
private:

};

class Sound_Interface : public Audio_Manager{
public:
    void update();
protected:
private:
    void play();

    std::queue<sf::SoundBuffer> library;

    std::map<std::string, sf::Sound> sounds;

    std::map<std::string, sf::Clock> thresholds;
};

class Music_Interface : public Audio_Manager{
public:
    void update();
protected:
private:
    void readBus();

    enum State{
        FADE_IN,
        PLAYING,
        FADE_OUT,
        NULLSTATE
    };

    State state{ FADE_IN };

    sf::Clock change_clock;
    unsigned int change_threshold{ 500 };

    sf::Music music;
};
/*

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
    static void update();
protected:
private:
};*/

class Audio_Settings : public Audio_Manager{
public:
    static void setVolumeMusic(float nv);
    static float getVolumeMusic();
    static void setVolumeGame(float nv);
    static float getVolumeGame();
    static void setVolumeUI(float nv);
    static float getVolumeUI();
};
