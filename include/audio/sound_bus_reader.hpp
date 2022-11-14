#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <map>

#include "sound_bus.hpp"
#include "sound_player.hpp"
#include "sound.hpp"

// this class converts Sound_Game and Sound_UI types into sf::Sound objects, which are then passed to Sound_Player

class Sound_Bus_Reader : private Sound_Player {
public:
    Sound_Bus_Reader();

    void read(Sound_Player& player);

private:
    Sound_Bus bus;
    std::map<Sound_Game, sf::SoundBuffer> game_sounds;
    std::map<Sound_UI, sf::SoundBuffer> ui_sounds;
};
