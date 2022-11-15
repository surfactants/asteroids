#pragma once

#include "sound_player.hpp"
#include "sound_bus_reader.hpp"

class Sound_Interface {
public:
    Sound_Interface() = default;

    void update();

protected:
    Sound_Bus_Reader busReader;
    Sound_Player player;
};
