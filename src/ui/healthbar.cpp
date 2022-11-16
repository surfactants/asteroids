#include <ui/healthbar.hpp>

#include <util/primordial.hpp>

Healthbar::Healthbar()
{
    frame.setOutlineThickness(1.f);
    frame.setOutlineColor(sf::Color(222, 222, 222));
}

void Healthbar::setSize(sf::Vector2f size)
{
    frame.setSize(size);
    setFill();
    setPosition(frame.getPosition());
}

void Healthbar::setPosition(sf::Vector2f pos)
{
    frame.setPosition(pos);
    fill.setPosition(pos);
}

void Healthbar::update(int hpCurrent, int hpMax)
{
    if(hpCurrent == this->hpCurrent
    && hpMax == this->hpMax) {
        return;
    }

    this->hpCurrent = hpCurrent;
    this->hpMax = hpMax;

    hpPercent = static_cast<float>(hpCurrent) / static_cast<float>(hpMax);

    setFill();
}

void Healthbar::setColors(sf::Color frameColor, sf::Color fillColor)
{
    frame.setFillColor(frameColor);
    fill.setFillColor(fillColor);
}

void Healthbar::setHidden(bool hidden)
{
    this->hidden = hidden;
}

void Healthbar::setFill()
{
    sf::Vector2f fillSize(size.x * hpPercent, size.y);
    fill.setSize(fillSize);
}

void Healthbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!hidden) {
        target.draw(frame, states);
        target.draw(fill, states);
    }
}

//////////////////////////////////////////////////////////////////////////

void UI_Healthbar::setFont(const sf::Font& font)
{
    nameText.setFont(font);
    levelText.setFont(font);
    healthText.setFont(font);
}

void UI_Healthbar::setNameText(std::string str)
{
    nameText.setString(str);
}

void UI_Healthbar::setLevelText(std::string str)
{
    levelText.setString(str);
}

void UI_Healthbar::center()
{
    frame.setOrigin(size / 2.f);
    fill.setOrigin(size / 2.f);

    nameText.setPosition(frame.getPosition() - sf::Vector2f(256.f, 0.f));
    centerText(nameText);
}

void UI_Healthbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!hidden) {
        target.draw(frame, states);
        target.draw(fill, states);

        target.draw(nameText, states);
        target.draw(levelText, states);
        target.draw(healthText, states);
    }
}
