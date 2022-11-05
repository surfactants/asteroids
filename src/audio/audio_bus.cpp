#include <audio/audio_bus.hpp>

std::string Audio_Bus::next_song;
std::queue<std::string> Audio_Bus::next_sounds;

bool Audio_Bus::song_change = false;

void Audio_Bus::addSound(std::string id)
{
    next_sounds.push(id);
}

void Audio_Bus::addMusic(std::string id)
{
    if (next_song != id) {
        next_song = "soundtrack/" + id + ".wav";
        song_change = true;
    }
}

std::string Audio_Bus::nextSound()
{
    std::string s = next_sounds.front();
    next_sounds.pop();
    return s;
}

std::string Audio_Bus::nextSong()
{
    song_change = false;
    return next_song;
}

bool Audio_Bus::songChanging()
{
    return song_change;
}
