#pragma once

#include "sqlite/sqlite3.h"
#include "settings_package.hpp"
#include <string>

class Database{
public:
    Database();

    static void saveSettings(Settings_Package p);
    static Settings_Package getSettings();
private:
    static int callback(void* notUsed, int argc, char** argv, char** azColName);

    static sqlite3* db;

    static void open();
    static void execute(std::string& sql);
    static void close();

    static int rc;
};
