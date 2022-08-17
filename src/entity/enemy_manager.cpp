#include <entity/enemy_manager.hpp>
#include <util/prng.hpp>
#include <resources/texture_manager.hpp>
#include <system/database.hpp>

Enemy_Manager::Enemy_Manager(){
    lowLevel = 8;
    highLevel = 13;

    loadPrototypes();

}

void Enemy_Manager::spawn(std::vector<Room>& rooms, float tileSize){
    reset();
    for(unsigned int r = 0; r < rooms.size() - 1; ++r){
            //r should start at 1, this is for debugging
        unsigned int enemyCount = prng::number(12u, 24u);
        std::vector<sf::Vector2i> used;
        for(unsigned int e = 0; e < enemyCount; ++e){
            sf::Vector2i c = rooms[r].coordinates;
            sf::Vector2i o(0, 0);
            do{
                c -= o;
                o.x = prng::number(-rooms[r].size.x / 2, rooms[r].size.x / 2);
                o.y = prng::number(-rooms[r].size.y / 2, rooms[r].size.y / 2);
                c += o;
                for(const auto& u : used){
                    if(c == u) continue;
                }
            } while(!rooms[r].contains(c));
            enemies.push_back(prototypes[currentFaction][MELEE_LIGHT]);
            enemies.back().setPosition(sf::Vector2f(c) * tileSize);
            enemies.back().setLevel(prng::number(lowLevel, highLevel));
            enemies.back().getSprite().setDirection(randomDirection());

            used.push_back(c);
        }
    }

    //place boss
    enemies.push_back(prototypes[currentFaction][BOSS]);
    enemies.back().setPosition(sf::Vector2f(rooms.back().coordinates) * tileSize);
    enemies.back().setLevel(highLevel + 1);
}

void Enemy_Manager::reset(){
    enemies.clear();
    currentFaction = static_cast<Faction>(prng::number(0, static_cast<int>(PLAYER_FACTION) - 1));
    currentFaction = BUGS;
}

void Enemy_Manager::clear(){
    enemies.clear();
}

void Enemy_Manager::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(const auto& enemy : enemies){
        target.draw(enemy, states);
    }
}

std::vector<Enemy>& Enemy_Manager::getEnemies(){
    return enemies;
}

void Enemy_Manager::loadPrototypes(){
    std::vector<Entity_Data> enemies = Database::getEnemies();

    std::map<Faction, std::map<Entity_Type, Enemy>>& p = prototypes;

    for(auto& e : enemies){
        std::string f(factionToString(e.faction)), t(entityTypeToString(e.type));
        std::string texture_key = std::string(factionToString(e.faction) + "-" + entityTypeToString(e.type));
        p[e.faction][e.type] = Enemy(e, Texture_Manager::get(texture_key));
    }
}

bool Enemy_Manager::checkFinalBoss(){
    return (enemies.back().getState() == DEAD);
}
