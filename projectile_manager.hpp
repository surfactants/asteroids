#pragma once

#include "projectile.hpp"
#include "entity.hpp"

class Projectile_Manager : public sf::Drawable{
public:
    Projectile_Manager();

    void create(Projectile p);

    void update();

    std::vector<Projectile>& getProjectiles();

protected:

private:
    std::vector<Projectile> projectiles;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
