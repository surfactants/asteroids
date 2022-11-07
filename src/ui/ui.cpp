#include <ui/ui.hpp>
#include <resources/texture_manager.hpp>

UI::UI(Game& ngame)
    : game { ngame }
{
}

void UI::update()
{
    minimap.update(game.getEnemies(), game.getPlayer().getPosition());

    for(auto& icon : playerAbilities){
        icon.update();
    }
}

void UI::clickLeft()
{
    //if ui parses the click then return
    //else...
    game.clickLeft();
}

void UI::releaseLeft()
{
    //ui parse, NO IF; player needs to stop shooting
    game.releaseLeft();
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(const auto& icon : playerAbilities){
        target.draw(icon, states);
    }

    //minimap defines its own view, so it must be drawn after anything that uses the main UI view
    target.draw(minimap, states);
}

void UI::scale(sf::RenderWindow& window)
{
    minimap.set(sf::Vector2f(window.getSize()));
}

void UI::stopInput()
{
    game.stopInput();
}

void UI::loadPlayerAbilities(const std::vector<Ability>& abilities)
{
    playerAbilities.clear();
    sf::Vector2f pos(8.f, 8.f);
    for(const auto& a : abilities){
        playerAbilities.push_back(Ability_Icon(a));
        playerAbilities.back().setTexture(Texture_Manager::get("ABILITIES"));

        sf::Vector2i spos(a.sheetIndex * 64, 0);
        sf::Vector2i ssize(64, 64);
        sf::IntRect textureRect(spos, ssize);
        playerAbilities.back().setTextureRect(textureRect);

        playerAbilities.back().setPosition(pos);
        pos.y += 72.f;
    }
}
