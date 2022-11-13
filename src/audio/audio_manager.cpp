#include <audio/audio_manager.hpp>

///////////////////////////////////////////////////
//BEGIN AUDIO MANAGER IMPLEMENTATION
//
void Sound_Interface::update()
{
    if (sounds_game.size() > 0 && sounds_game.front().getStatus() == sf::Sound::Stopped)
        sounds_game.pop_front();
    if (sounds_ui.size() > 0 && sounds_ui.front().getStatus() == sf::Sound::Stopped)
        sounds_ui.pop_front();
}

void Sound_Interface::playSound(sf::Sound sound)
{
    sounds_game.push_back(sound);
    sounds_game.back().setVolume(volume_game);
    sounds_game.back().play();
}

void Sound_Interface::playUI(sf::Sound sound)
{
    sounds_ui.push_back(sound);
    sounds_ui.back().setVolume(volume_ui);
    sounds_ui.back().play();
}
//
//END AUDIO MANAGER IMPLEMENTATION
///////////////////////////////////////////////////

void Sound_Interface::update()
{
    if (sounds_game.size() > 0 && sounds_game.front().getStatus() == sf::Sound::Stopped)
        sounds_game.pop_front();
}

///////////////////////////////////////////////////
//BEGIN AUDIO SETTINGS IMPLEMENTATION
//
void Audio_Settings::setVolumeMusic(float nv)
{
    volume_music = nv;
}

float Audio_Settings::getVolumeMusic()
{
    return volume_music;
}

void Audio_Settings::setVolumeGame(float nv)
{
    volume_game = nv;
    for (auto& it : sounds_game)
        it.setVolume(volume_game);
}

float Audio_Settings::getVolumeGame()
{
    return volume_game;
}

void Audio_Settings::setVolumeUI(float nv)
{
    volume_ui = nv;
    for (auto& it : sounds_ui)
        it.setVolume(volume_ui);
}

float Audio_Settings::getVolumeUI()
{
    return volume_ui;
}
//
//END AUDIO SETTINGS IMPLEMENTATION
///////////////////////////////////////////////////
