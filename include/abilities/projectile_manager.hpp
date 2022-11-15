#pragma once

#include <SFML/Graphics.hpp>

#include "projectile.hpp"

/////////////////////////////////////////////////////////////
/// \brief
///
class Projectile_Manager : public sf::Drawable {
public:
    Projectile_Manager();

    void create(Projectile p);

    void update(float deltaTime);

    std::vector<Projectile>& getProjectiles();

protected:
private:
    std::vector<Projectile> projectiles;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
