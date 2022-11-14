#pragma once

#include "sound_player.hpp"

class Audio_Settings : private Sound_Player {
public:
    static void setVolumeMusic(float nv);
    static float getVolumeMusic();

    static void setVolumeGame(float nv);
    static float getVolumeGame();

    static void setVolumeUI(float nv);
    static float getVolumeUI();
};
