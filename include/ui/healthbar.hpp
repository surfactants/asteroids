#pragma once

#include <SFML/Graphics.hpp>

class Healthbar : public sf::Drawable {
public:
    Healthbar();

    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f pos);

    void update(int hpCurrent, int hpMax);

    void setHidden(bool hidden);

    virtual void center();

protected:
    sf::RectangleShape frame;
    sf::RectangleShape fill;

    bool hidden{ false };

    int hpCurrent{ 1 };
    int hpMax{ 1 };
    float hpPercent{ 1.f };

    void setFill();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class UI_Healthbar : public Healthbar {
public:
    UI_Healthbar() : Healthbar() {}

    void setFont(const sf::Font& font);

    void setNameText(std::string str);
    void setLevelText(std::string str);

    virtual void center() override;

private:
    sf::Text nameText;
    sf::Text levelText;
    sf::Text healthText;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
