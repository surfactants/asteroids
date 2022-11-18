#include <ui/ui.hpp>

#include <resources/texture_manager.hpp>

#include <resources/font_manager.hpp>

#include <util/vector2_stream.hpp>

//////////////////////////////////////////////////////////////

UI::UI(Game& game)
    : game { game }
    , font{ Font_Manager::get(Font::UI) }
    , entityInfo{ Font_Manager::get(Font::UI) }
{
    defineHealthbars();
}

void UI::defineHealthbars()
{
    sf::Vector2f pos(16.f, 16.f);
    sf::Vector2f size(256.f, 28.f);
    player_health.setPosition(pos);
    player_health.setSize(size);

    pos = sf::Vector2f((1920.f / 2.f), 1000.f);
    size = sf::Vector2f(590.f, 62.f);
    boss_health.setPosition(pos);
    boss_health.setSize(size);
    boss_health.setFont(font);
    boss_health.setNameText("boss");
    boss_health.center();
}

void UI::update()
{
    minimap.update(game.getEnemies(), game.getPlayer().getPosition());

    for (auto& icon : playerAbilities) {
        icon.update();
    }

    updateHealthbars();
}

void UI::setMouseover(Entity* entity)
{
    entityInfo.update(entity);
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

void UI::scale(sf::RenderWindow& window)
{
    minimap.set(sf::Vector2f(window.getSize()));

    sf::Vector2f pos = minimap.getPosition();
    pos.x *= window.getSize().x;
    pos.y *= window.getSize().y;
    sf::Vector2f size = minimap.getSize();
        pos.y += size.y + 8.f;
    //size.y = 320.f;

    entityInfo.set(pos, size);
}

void UI::stopInput()
{
    game.stopInput();
}

void UI::newLevel()
{
    boss_health.setHidden(true);
    updateHealthbars();
}

void UI::loadPlayerAbilities(const std::vector<Ability>& abilities)
{
    playerAbilities.clear();
    sf::Vector2f pos(16.f, 64.f);
    for (const auto& a : abilities) {
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

void UI::resize(sf::Vector2u windowSize)
{}

void UI::updateHealthbars()
{
    const Enemy& boss = game.getBoss();
    boss_health.setNameText(boss.getName());
    boss_health.update(boss.getHPCurrent(), boss.getHPMax());

    const Player& player = game.getPlayer();
    player_health.update(player.getHPCurrent(), player.getHPMax());
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& icon : playerAbilities) {
        target.draw(icon, states);
    }

    target.draw(player_health, states);
    target.draw(boss_health, states);

    target.draw(entityInfo, states);

    //minimap MUST be drawn last, as it defines its own view
    target.draw(minimap, states);
}
