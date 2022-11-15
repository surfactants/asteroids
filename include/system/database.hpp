#pragma once

#include <SFML/Audio/SoundBuffer.hpp>

#include <SFML/Graphics.hpp>

#include <map>
#include <string>

#include <animation/animation.hpp>

#include <audio/sound.hpp>
#include <audio/sound_context.hpp>

#include <entity/enemy.hpp>
#include <entity/faction.hpp>

#include <input/action.hpp>

#include <resources/font.hpp>

#include <sqlite3.h>

#include <world/tile.hpp>

#include "settings_package.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
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

    static void loadSounds(std::map<Sound_Game, Sound_Context>& game_sounds,
        std::map<Sound_UI, Sound_Context>& ui_sounds);

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
