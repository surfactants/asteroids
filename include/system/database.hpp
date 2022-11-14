#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <animation/animation.hpp>
#include <entity/enemy.hpp>
#include <entity/faction.hpp>
#include <input/action.hpp>
#include <map>
#include <resources/font.hpp>
#include <sqlite3.h>
#include <string>
#include <system/settings_package.hpp>
#include <world/tile.hpp>
#include <audio/sound.hpp>

class Database {
public:
    ~Database();

    static void saveSettings(Settings_Package p);
    static Settings_Package getSettings();

    static void getTextures(std::map<std::string, sf::Texture>& t);

    static std::map<Entity_State, Animation> getAnimations();

    static std::vector<Entity_Data> getEnemies();

    static Entity_Data getPlayerData();

    static void getFonts(std::map<Font, sf::Font>& f);

    static std::map<Faction, Hazard_Data> getHazards();

    static std::map<Faction, std::string> getAutotileRules();

    static std::map<std::string, Action_Trigger> getActions();

    static void saveActions(std::vector<Action> actions);

    static std::map<std::string, Ability> getAbilities();

    static void loadSounds(std::map<Sound_Game, sf::SoundBuffer>& game_sounds,
        std::map<Sound_UI, sf::SoundBuffer>& ui_sounds);

private:
    static int callback(void* notUsed, int argc, char** argv, char** azColName);

    static sqlite3* db;

    static void open();
    static void execute(std::string& sql);
    static void close();

    static int rc;

    static void errorCheck(std::string id);

    static std::vector<char*> font_buffers;

    static Entity_Data readEntity(sqlite3_stmt* statement);
};
