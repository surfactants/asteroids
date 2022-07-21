#include "database.hpp"

sqlite3* Database::db = nullptr;

int Database::rc = 0;

Database::Database(){
}

void Database::saveSettings(Settings_Package p){
    open();

std::string sql =
    "UPDATE VOLUME SET VALUE = '" + std::to_string(p.volume[VOL_MUSIC]) + "' WHERE ID = 'MUSIC';" \
    "UPDATE VOLUME SET VALUE = '" + std::to_string(p.volume[VOL_GAME]) + "' WHERE ID = 'GAME';" \
    "UPDATE VOLUME SET VALUE = '" + std::to_string(p.volume[VOL_UI]) + "' WHERE ID = 'UI';";

    execute(sql);

    close();
}

Settings_Package Database::getSettings(){
    Settings_Package p;

        open();

            sqlite3_stmt* statement;

std::string sql =
            "SELECT * FROM 'VOLUME'";

            rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

            while((rc = sqlite3_step(statement)) == SQLITE_ROW){
                std::string id( reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
                Volume_Type type;
                if(id == "MUSIC"){
                    type = VOL_MUSIC;
                }
                else if(id == "GAME"){
                    type = VOL_GAME;
                }
                else if(id == "UI"){
                    type = VOL_UI;
                }
                else continue;

                p.volume[type] = sqlite3_column_double(statement, 1);
            }

        close();

    return p;
}

void Database::open(){
    rc = sqlite3_open("data.db", &db);
}

void Database::execute(std::string& sql){
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, NULL);
}

void Database::close(){
    rc = sqlite3_close(db);
}

int Database::callback(void* notUsed, int argc, char** argv, char** azColName){
    return 0;
}

void Database::getTextures(std::map<std::string, sf::Texture>& t){
    open();

    std::string sql = "SELECT * FROM 'TEXTURES';";

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);
    int row = 0;
    while((rc = sqlite3_step(statement)) == SQLITE_ROW){
        std::string id = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));

        sf::Texture texture;
            sqlite3_blob* blob;

            rc = sqlite3_blob_open(db, "main", "TEXTURES", "DATA", ++row, 0, &blob);

            int bsize = sqlite3_blob_bytes(blob);
            char* buffer = new char[bsize];

            rc = sqlite3_blob_read(blob, buffer, bsize, 0);

            texture.loadFromMemory(buffer, bsize);
            delete[] buffer;

            sqlite3_blob_close(blob);

        t[id] = texture;
    }
    rc = sqlite3_finalize(statement);

    close();
}
