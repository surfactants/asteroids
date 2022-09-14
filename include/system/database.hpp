#pragma once

#include <sqlite/sqlite3.h>
#include <system/settings_package.hpp>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <animation/animation.hpp>
#include <entity/enemy.hpp>
#include <resources/font.hpp>
#include <string>
#include <entity/faction.hpp>
#include <world/tile.hpp>

class Database{
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
