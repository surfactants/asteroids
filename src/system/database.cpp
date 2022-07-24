#include <system/database.hpp>
#include <animation/animation.hpp>

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

std::vector<Entity_Data> Database::getEnemies(){
    std::vector<Entity_Data> enemies;

    open();

    std::string sql = "SELECT * FROM 'ENTITIES' WHERE NAME != 'PLAYER';";

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while((rc = sqlite3_step(statement)) == SQLITE_ROW){
        enemies.push_back(Entity_Data());
        Entity_Data& e = enemies.back();
            //name text
            //faction text
            //type text
            //size_x int
            //size_y int
            //moving_count int
            //dying_count int
            //idle_count int

        int column = 0;

        e.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, column++));
        e.faction = stringToFaction(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
        e.type = stringToEntityType(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
        int x = sqlite3_column_int(statement, column++);
        int y = sqlite3_column_int(statement, column++);
        e.size = sf::Vector2i(x, y);
        e.aCount[MOVING] = sqlite3_column_int(statement, column++);
        e.aCount[DYING] = sqlite3_column_int(statement, column++);
        e.aCount[IDLE] = sqlite3_column_int(statement, column++);
    }

    close();

    return enemies;
}

std::map<Animation_State, Animation> Database::getAnimations(){
    open();

    std::string sql = "SELECT * FROM 'ANIMATIONS';";

    close();

    return std::map<Animation_State, Animation>();
}

Entity_Data Database::getPlayerData(){
    Entity_Data p;

    open();

    std::string sql = "SELECT * FROM 'ENTITIES' WHERE NAME = 'PLAYER';";

    execute(sql);

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while((rc = sqlite3_step(statement)) == SQLITE_ROW){
            //name text
            //faction text
            //type text
            //size_x int
            //size_y int
            //moving_count int
            //dying_count int
            //idle_count int

        int column = 0;

        p.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, column++));
        p.faction = stringToFaction(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
        p.type = stringToEntityType(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
        int x = sqlite3_column_int(statement, column++);
        int y = sqlite3_column_int(statement, column++);
        p.size = sf::Vector2i(x, y);
        p.aCount[MOVING] = static_cast<unsigned int>(sqlite3_column_int(statement, column++));
        p.aCount[DYING] = static_cast<unsigned int>(sqlite3_column_int(statement, column++));
        p.aCount[IDLE] = static_cast<unsigned int>(sqlite3_column_int(statement, column++));
    }

    close();

    return p;
}
