#pragma once

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <deque>

//interface sounds from kenney.nl

class Sound_Player {
public:
    Sound_Player() = default;

    void addGameSound(const sf::SoundBuffer& sound);
    void addUISound(const sf::SoundBuffer& sound);

    void update();

protected:
    static float volume_music;
    static sf::Music music;

    static std::deque<sf::Sound> sounds;

    static float volume_game;
    static std::deque<sf::Sound> sounds_game;

    static float volume_ui;
    static std::deque<sf::Sound> sounds_ui;
};
