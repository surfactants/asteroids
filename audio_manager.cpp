#include "audio_manager.hpp"

///////////////////////////////////////////////////
//BEGIN AUDIO MANAGER IMPLEMENTATION
//
void Audio_Manager::update(){
    if(sounds_game.size() > 0 && sounds_game.front().getStatus() == sf::Sound::Stopped) sounds_game.pop_front();
    if(sounds_ui.size() > 0 && sounds_ui.front().getStatus() == sf::Sound::Stopped) sounds_ui.pop_front();
}

void Audio_Manager::playSound(){
    sounds_game.push_back(sf::Sound(s_whatever));
    sounds_game.back().setVolume(volume_sound);
    sounds_game.play();
}

void Audio_Manager::playUI(){
    sounds_ui.push_back(sf::Sound(s_whatever));
    sounds_ui.back().setVolume(volume_ui);
    sounds_ui.back().play();
}
//
//END AUDIO MANAGER IMPLEMENTATION
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//BEGIN AUDIO SETTINGS IMPLEMENTATION
//
void Audio_Settings::setVolumeMusic(float nv){
    volume_music = nv;
}

void Audio_Settings::setVolumeSound(float nv){
    volume_sound = nv;
    for(auto& it : sounds_game) it.setVolume(volume_sound);
}

void Audio_Settings::setVolumeUI(float nv){
    volume_ui = nv;
    for(auto& it : sounds_ui) it.setVolume(volume_ui);
}
//
//END AUDIO SETTINGS IMPLEMENTATION
///////////////////////////////////////////////////
