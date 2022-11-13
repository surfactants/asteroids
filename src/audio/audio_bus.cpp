#include <audio/audio_bus.hpp>

Song Audio_Bus::next_song;

std::queue<Sound> Audio_Bus::next_sound;

void Audio_Bus::addSound(Sound sound)
{
    //next_game_sounds.push(sounds_game[sound]);
}
void Audio_Bus::addSong(Song song)
{
    if (next_song != song) {
        //std::string fname = songToString(song);
        //next_song = "soundtrack/" + fname + ".wav";
        next_song = song;
    }
}

Sound Audio_Bus::nextSound()
{
    if(!next_sound.empty()) {
        Sound s = next_sound.front();
        next_sound.pop();
        return s;
    }
    else return Sound::NULL_SOUND;
}

Song Audio_Bus::nextSong()
{
    if (next_song != Song::NULL_SONG) {
        Song s = next_song;
        next_song = Song::NULL_SONG;
        return s;
    }
    else return next_song;
}
