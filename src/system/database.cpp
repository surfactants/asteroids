#include <animation/animation.hpp>
#include <input/key_char.hpp>
#include <system/database.hpp>
#include <entity/ability_type.hpp>

sqlite3* Database::db = nullptr;
std::vector<char*> Database::font_buffers = std::vector<char*>();

int Database::rc = 0;

Database::~Database()
{
    for (unsigned int i = 0; i < font_buffers.size(); ++i) {
        delete[] font_buffers[i];
    }
}

void Database::saveSettings(Settings_Package p)
{
    open();

    for (const auto& v : p.volume) {
        std::string sql = "UPDATE VOLUME SET VALUE = '" + std::to_string(v.second) + "' WHERE ID = '" + volumeTypeToString(v.first) + "';";
        execute(sql);
    }

    close();
}

Settings_Package Database::getSettings()
{
    Settings_Package p;

    open();

    sqlite3_stmt* statement;

    std::string sql = "SELECT * FROM 'VOLUME'";

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        std::string id(reinterpret_cast<const char*>(sqlite3_column_text(statement, 0)));
        p.volume[stringToVolumeType(id)] = sqlite3_column_double(statement, 1);
    }

    sqlite3_finalize(statement);

    close();

    return p;
}

void Database::open()
{
    rc = sqlite3_open("data.db", &db);
}

void Database::execute(std::string& sql)
{
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, NULL);
}

void Database::close()
{
    rc = sqlite3_close(db);
}

int Database::callback(void* notUsed, int argc, char** argv, char** azColName)
{
    return 0;
}

void Database::getTextures(std::map<std::string, sf::Texture>& t)
{
    open();

    std::string sql = "SELECT * FROM 'TEXTURES';";

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    int row = 0;
    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
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

std::vector<Entity_Data> Database::getEnemies()
{
    std::vector<Entity_Data> enemies;

    open();

    std::string sql = "SELECT * FROM 'ENTITIES' WHERE NAME != 'PLAYER';";

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        enemies.push_back(readEntity(statement));
    }

    sqlite3_finalize(statement);

    close();

    return enemies;
}

std::map<Entity_State, Animation> Database::getAnimations()
{
    open();

    std::string sql = "SELECT * FROM 'ANIMATIONS';";

    close();

    return std::map<Entity_State, Animation>();
}

Entity_Data Database::getPlayerData()
{
    Entity_Data p;

    open();

    std::string sql = "SELECT * FROM 'ENTITIES' WHERE NAME = 'PLAYER';";

    execute(sql);

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        p = readEntity(statement);
    }

    sqlite3_finalize(statement);

    close();

    return p;
}

Entity_Data Database::readEntity(sqlite3_stmt* statement)
{
    int column = 0;

    Entity_Data d;
    //base data
    //name text
    //faction text
    //type text
    //speed double

    d.name = reinterpret_cast<const char*>(sqlite3_column_text(statement, column++));
    d.faction = stringToFaction(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
    d.type = stringToEntityType(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
    d.speed = sqlite3_column_double(statement, column++);

    //size data
    //size_x int
    //size_y int

    int x = sqlite3_column_int(statement, column++);
    int y = sqlite3_column_int(statement, column++);
    d.size = sf::Vector2i(x, y);

    //resistances
    //sharp float
    //blunt float
    //bullet float
    //acid float
    //explosive float
    //fire float
    //plasma float
    //laser float
    //electric float

    d.resistance[Damage::SHARP] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::BLUNT] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::BULLET] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::ACID] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::EXPLOSIVE] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::FIRE] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::PLASMA] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::LASER] = sqlite3_column_double(statement, column++);
    d.resistance[Damage::ELECTRIC] = sqlite3_column_double(statement, column++);

    //animation counts
    //idle_count int
    //moving_count int
    //casting_count int
    //dying_count int

    d.aCount[Entity_State::IDLE] = static_cast<unsigned int>(sqlite3_column_int(statement, column++));
    d.aCount[Entity_State::MOVING] = static_cast<unsigned int>(sqlite3_column_int(statement, column++));
    d.aCount[Entity_State::CASTING] = static_cast<unsigned int>(sqlite3_column_int(statement, column++));
    d.aCount[Entity_State::DYING] = static_cast<unsigned int>(sqlite3_column_int(statement, column++));

    //animation thresholds
    //idle_threshold int
    //moving_threshold int
    //casting_threshold int
    //dying_threshold int

    d.aThreshold[Entity_State::IDLE] = sqlite3_column_int(statement, column++);
    d.aThreshold[Entity_State::MOVING] = sqlite3_column_int(statement, column++);
    d.aThreshold[Entity_State::CASTING] = sqlite3_column_int(statement, column++);
    d.aThreshold[Entity_State::DYING] = sqlite3_column_int(statement, column++);

    return d;
}

void Database::getFonts(std::map<Font, sf::Font>& f)
{
    open();

    std::string sql = "SELECT * FROM 'FONTS';";

    sqlite3_stmt* statement;

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    int row = 0;

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        int column = 0;
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(statement, column));

        sqlite3_blob* blob;

        rc = sqlite3_blob_open(db, "main", "FONTS", "DATA", ++row, 0, &blob);
        errorCheck(std::string("opening font blob " + name));

        int bsize = sqlite3_blob_bytes(blob);
        font_buffers.push_back(new char[bsize]);

        rc = sqlite3_blob_read(blob, font_buffers.back(), bsize, 0);
        errorCheck(std::string("\treading font blob " + name));

        f[stringToFont(name)].loadFromMemory(font_buffers.back(), bsize);

        rc = sqlite3_blob_close(blob);
    }

    sqlite3_finalize(statement);

    close();
}

std::map<Faction, Hazard_Data> Database::getHazards()
{
    std::map<Faction, Hazard_Data> hazards;

    open();

    sqlite3_stmt* statement;

    std::string sql = "SELECT * FROM 'HAZARDS'";

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        unsigned int column = 0;
        Faction faction = stringToFaction(std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++))));

        hazards[faction].damage.type = stringToDamageType(std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++))));
        hazards[faction].damage.val = sqlite3_column_int(statement, column++);
        hazards[faction].index = sqlite3_column_int(statement, column++);
    }

    sqlite3_finalize(statement);

    close();

    return hazards;
}

std::map<Faction, std::string> Database::getAutotileRules()
{
    open();

    sqlite3_stmt* statement;

    std::string sql = "SELECT * FROM 'AUTOTILED'";

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    std::map<Faction, std::string> rules;

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        unsigned int column = 0;
        Faction faction = stringToFaction(std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++))));

        rules[faction] = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
    }

    sqlite3_finalize(statement);

    close();

    return rules;
}

void Database::errorCheck(std::string id)
{
    //std::cout << id + ": " + sqlite3_errmsg(db) << '\n';
    //log error message here
}

std::map<std::string, sf::Keyboard::Key> Database::getActions()
{
    open();

    sqlite3_stmt* statement;

    std::string sql = "SELECT * FROM 'COMMANDS'";

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    std::map<std::string, sf::Keyboard::Key> actions;

    Convert_Key converter;

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        unsigned int column = 0;
        std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
        std::string key = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));

        actions[name] = converter.toKey(key);
    }

    sqlite3_finalize(statement);

    close();

    return actions;
}

void Database::saveActions(std::vector<Action> actions)
{
    open();

    std::string sql = "DELETE FROM COMMANDS";

    execute(sql);

    sql = "VACUUM";

    execute(sql);

    Convert_Key converter;

    for (const auto& action : actions) {
        sql = "INSERT INTO COMMANDS(NAME, KEY) VALUES(\"" + action.name + "\", \"" + converter.toString(std::get<sf::Keyboard::Key>(action.key)) + "\");";
        execute(sql);
    }

    close();
}

std::map<std::string, Ability> Database::getAbilities()
{
    std::map<std::string, Ability> abilities;

    open();

    sqlite3_stmt* statement;

    std::string sql = "SELECT * FROM ABILITIES";

    rc = sqlite3_prepare_v2(db, sql.c_str(), sql.length(), &statement, NULL);

    size_t index = 0;

    while ((rc = sqlite3_step(statement)) == SQLITE_ROW) {
        unsigned int column = 0;
        std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(statement, column++)));
        Ability_Type type = stringToAbilityType(name);
        size_t magnitude = sqlite3_column_int(statement, column++);
        size_t range = sqlite3_column_int(statement, column++);
        size_t radius = sqlite3_column_int(statement, column++);
        double cooldown = sqlite3_column_double(statement, column++);
        double duration = sqlite3_column_double(statement, column++);
        double speed = sqlite3_column_double(statement, column++);

        Ability a;
            a.type = type;
            a.sheetIndex = index;
            a.magnitude = magnitude;
            a.radius = radius;
            a.cooldown = cooldown;
            a.duration = duration;
            Damage dmg(magnitude, Damage::LASER);
            a.projectile = Projectile(type, speed, dmg, range);
        abilities[name] = a;

        index++;
    }

    sqlite3_finalize(statement);

    close();

    return abilities;
}
