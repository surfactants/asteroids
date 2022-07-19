#include "audio_manager.hpp"

float Audio_Manager::volume_music = 100.f;

float Audio_Manager::volume_game = 100.f;

float Audio_Manager::volume_ui = 100.f;

std::deque<sf::Sound> Audio_Manager::sounds_game = std::deque<sf::Sound>();

std::deque<sf::Sound> Audio_Manager::sounds_ui = std::deque<sf::Sound>();

///////////////////////////////////////////////////
//BEGIN AUDIO MANAGER IMPLEMENTATION
//
void Audio_Manager::update(){
    if(sounds_game.size() > 0 && sounds_game.front().getStatus() == sf::Sound::Stopped) sounds_game.pop_front();
    if(sounds_ui.size() > 0 && sounds_ui.front().getStatus() == sf::Sound::Stopped) sounds_ui.pop_front();
}

void Audio_Manager::playSound(sf::Sound sound){
    sounds_game.push_back(sound);
    sounds_game.back().setVolume(volume_game);
    sounds_game.back().play();
}

void Audio_Manager::playUI(sf::Sound sound){
    sounds_ui.push_back(sound);
    sounds_ui.back().setVolume(volume_ui);
    sounds_ui.back().play();
}
//
//END AUDIO MANAGER IMPLEMENTATION
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//BEGIN AUDIO GAME IMPLEMENTATION
//
void Audio_Game::play(std::string id){
    if(sounds.count(id)) player.playSound(sf::Sound(sounds[id]));
}
//
//END AUDIO GAME IMPLEMENTATION
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//BEGIN AUDIO UI IMPLEMENTATION
//
void Audio_UI::play(std::string id){
    if(sounds.count(id)) player.playUI(sf::Sound(sounds[id]));
}
//
//END AUDIO UI IMPLEMENTATION
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//BEGIN AUDIO SETTINGS IMPLEMENTATION
//
void Audio_Settings::setVolumeMusic(float nv){
    volume_music = nv;
}

void Audio_Settings::setVolumeSound(float nv){
    volume_game = nv;
    for(auto& it : sounds_game) it.setVolume(volume_game);
}

void Audio_Settings::setVolumeUI(float nv){
    volume_ui = nv;
    for(auto& it : sounds_ui) it.setVolume(volume_ui);
}
//
//END AUDIO SETTINGS IMPLEMENTATION
///////////////////////////////////////////////////
