#include <ui/healthbar.hpp>

#include <resources/palette.hpp>

#include <util/primordial.hpp>

Healthbar::Healthbar()
{
    frame.setOutlineThickness(1.f);
    frame.setOutlineColor(sf::Color(222, 222, 222));

    sf::Color frameColor(0, 0, 0, 110);
    sf::Color fillColor(130, 16, 16);

    frame.setFillColor(frameColor);
    fill.setFillColor(fillColor);
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

void Healthbar::setHidden(bool hidden)
{
    this->hidden = hidden;
}

void Healthbar::setFill()
{
    sf::Vector2f fillSize(frame.getSize().x * hpPercent, frame.getSize().y);
    fill.setSize(fillSize);
}

void Healthbar::center()
{
    frame.setOrigin(frame.getSize() / 2.f);
    fill.setOrigin(frame.getSize() / 2.f);
}

void Healthbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(!hidden) {
        target.draw(frame, states);
        target.draw(fill, states);
    }
}

//////////////////////////////////////////////////////////////////////////

UI_Healthbar::UI_Healthbar() :
    Healthbar()
{
    nameText.setFillColor(palette::white);
    levelText.setFillColor(palette::white);
}

void UI_Healthbar::setFont(const sf::Font& font)
{
    nameText.setFont(font);
    levelText.setFont(font);
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
    Healthbar::center();
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
    }
}
