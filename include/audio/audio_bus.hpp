#pragma once

#include <queue>
#include <string>

class Audio_Bus {
protected:
    static void addSound(std::string id);
    static void addMusic(std::string id);

    static std::string nextSound();
    static std::string nextSong();

    static bool songChanging();

    static std::queue<std::string> next_sounds;
    static std::string next_song;
    static bool song_change;
};
