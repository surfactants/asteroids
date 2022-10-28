#include <audio/audio_manager.hpp>

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

void Sound_Interface::update(){
    if(sounds_game.size() > 0 && sounds_game.front().getStatus() == sf::Sound::Stopped) sounds_game.pop_front();
}

void Sound_Interface::play(){
}

void Music_Interface::update(){
    switch(state){
        case FADE_IN:
            break;
        case PLAYING:
            if(song_change){
                state = FADE_OUT;
            }
            break;
        case FADE_OUT:
            if(music.getVolume() == 0.f){
                change_clock.restart();
                state = NULLSTATE;
            }
            break;
        case NULLSTATE:
            if(change_clock.getElapsedTime().asMilliseconds() >= change_threshold){
                state = FADE_IN;
                music.openFromFile(nextSong());
            }
            break;
    }
}


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
//BEGIN AUDIO MUSIC IMPLEMENTATION
//
void Audio_Music::play(std::string id){
    //music.loadFromFile("soundtrack" + id + ".wav");
}
//
//END AUDIO MUSIC IMPLEMENTATION
///////////////////////////////////////////////////

///////////////////////////////////////////////////
//BEGIN AUDIO SETTINGS IMPLEMENTATION
//
void Audio_Settings::setVolumeMusic(float nv){
    volume_music = nv;
}

float Audio_Settings::getVolumeMusic(){
    return volume_music;
}

void Audio_Settings::setVolumeGame(float nv){
    volume_game = nv;
    for(auto& it : sounds_game) it.setVolume(volume_game);
}

float Audio_Settings::getVolumeGame(){
    return volume_game;
}

void Audio_Settings::setVolumeUI(float nv){
    volume_ui = nv;
    for(auto& it : sounds_ui) it.setVolume(volume_ui);
}

float Audio_Settings::getVolumeUI(){
    return volume_ui;
}
//
//END AUDIO SETTINGS IMPLEMENTATION
///////////////////////////////////////////////////
