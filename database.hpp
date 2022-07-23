#pragma once

#include "sqlite/sqlite3.h"
#include "settings_package.hpp"
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include "animation.hpp"
#include "enemy.hpp"

class Database{
public:
    Database();

    static void saveSettings(Settings_Package p);
    static Settings_Package getSettings();

    static void getTextures(std::map<std::string, sf::Texture>& t);

    static std::map<Animation_State, Animation> getAnimations();

    static std::vector<Entity_Data> getEnemies();

    static Entity_Data getPlayerData();

private:
    static int callback(void* notUsed, int argc, char** argv, char** azColName);

    static sqlite3* db;

    static void open();
    static void execute(std::string& sql);
    static void close();

    static int rc;
};
