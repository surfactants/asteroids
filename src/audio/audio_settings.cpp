#include <audio/audio_settings.hpp>

void Audio_Settings::setVolumeMusic(float nv)
{
    volume_music = nv;
    music.setVolume(volume_music);
}

float Audio_Settings::getVolumeMusic()
{
    return volume_music;
}

void Audio_Settings::setVolumeGame(float nv)
{
    volume_game = nv;
    for (auto& it : sounds_game) {
        it.setVolume(volume_game);
    }
}

float Audio_Settings::getVolumeGame()
{
    return volume_game;
}

void Audio_Settings::setVolumeUI(float nv)
{
    volume_ui = nv;
    for (auto& it : sounds_ui) {
        it.setVolume(volume_ui);
    }
}

float Audio_Settings::getVolumeUI()
{
    return volume_ui;
}
