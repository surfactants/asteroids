#include <audio/sound_player.hpp>

float Sound_Player::volume_music = 100.f;

float Sound_Player::volume_game = 100.f;

float Sound_Player::volume_ui = 100.f;

std::deque<sf::Sound> Sound_Player::sounds_game = std::deque<sf::Sound>();
std::deque<sf::Sound> Sound_Player::sounds_ui = std::deque<sf::Sound>();
