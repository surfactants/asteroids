#pragma once

#include <SFML/Graphics.hpp>

#include <input/action.hpp>
#include <input/input_package.hpp>
#include <input/key_char.hpp>
#include <input/mouse_event.hpp>

//this will work great, i think, at the expense of a less generic input handler

//TODO:
// scrolling ? :(
// re-setting a key should swap with the previous binding (h/t oblivion)
// buttons (confirm, cancel, reset changes)

//recommend running checkMouse() every frame, for post-selection hovers

//need to figure out a better bridge to the input handler
//perhaps setting up an enum there?

/* EXAMPLE ************************************************************************
 *
 * Key_Mapper key_mapper(font);
 * key_mapper.setPosition(sf::Vector2f(128.f, 128.f));
 * std::vector<Action> actions;
 *     actions.push_back(Action("move north", std::function<void()>(), sf::Keyboard::W));
 *     actions.push_back(Action("move west", std::function<void()>(), sf::Keyboard::A));
 *     actions.push_back(Action("move south", std::function<void()>(), sf::Keyboard::S));
 *     actions.push_back(Action("move east", std::function<void()>(), sf::Keyboard::D));
 * key_mapper.setActions(actions);
 *
 **********************************************************************************/

// constructor (pass font ref)
// reset -
// setPosition - places the object - no origin is defined, so this is the top-left corner
// checkMouse() - updates highlight state. returns true if the mouse is in the object.
// clickLeft() - parses left mouse button press, used to select rows.
// keyPressed() - updates key of selected row, or cancels if it's Escape
// setTextColor()
// setBackgroundColor()
// setHoverColor()
// setSelectColor()
// setActions() - create rows from a vector of Action objects.
// getActions() - returns a vector of actions for linking to the input handler

/* PUBLIC METHODS *****************************************************************
 *
 * Key_Mapper(sf::Font& font)
 *     No default constructor
 *
 * void setActions(const std::vector<Action>& actions
 *     Creates rows from action class (name/function/key)
 *
 * std::vector<Action> getActions()
 *     ___
 *
 * void reset()
 *     unhovers, unselects, and reverts changes
 *
 * void confirm()
 *     unhovers, unselects, and saves changes
 *
 * void setPosition(sf::Vector2f pos)
 *     places the object - no origin is defined, so this is the top-left corner
 *
 * bool checkMouse(sf::Vector2i mpos)
 *     ___
 *
 * bool clickLeft()
 *     ___
 *
 * bool keyPressed(sf::Keyboard::Key key)
 *     ___
 *
 * void setTextColor(const sf::Color& color)
 *     ___
 *
 * void setBackgroundColor(const sf::Color& color)
 *     ___
 *
 * void setHoverColor(const sf::Color& color)
 *     ___
 *
 * void setSelectColor(const sf::Color& color)
 *     ___
 *
 **********************************************************************************/

class Key_Mapper : public sf::Drawable {
public:
    std::vector<Action> getActions();

    bool keyPressed(sf::Keyboard::Key key);

    void reset();

protected:
    Key_Mapper();

    void setActions(const sf::Font& font, const std::vector<Action>& actions);

    void confirm();

    void setPosition(sf::Vector2f pos);

    bool checkMouse(sf::Vector2f mpos);

    bool clickLeft();

    void setTextColor(const sf::Color& color);
    void setBackgroundColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);
    void setSelectColor(const sf::Color& color);

    class Row;

    Convert_Key converter;

    sf::Vector2f pos { 0.f, 0.f };
    sf::Vector2f rowSize { 512.f, 72.f };

    size_t hoverIndex { SIZE_MAX };
    size_t selectIndex { SIZE_MAX };

    std::vector<Row> rows;

    unsigned int characterSize = 36;

    void undoHover();
    void undoSelect();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

class Key_Mapper::Row : public sf::Drawable, public Action {
public:
    Row(const Action& action, const sf::Font& font, unsigned int characterSize, sf::Vector2f size);

    enum State {
        NONE,
        HOVER,
        SELECT
    };

    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f pos);

    const sf::Vector2f getSize() const;

    const static int padding = 6;

    bool checkMouse(sf::Vector2f mpos);

    void reset();
    void setKey(std::string key);
    void confirm();

    void resetColors();
    void setState(Row::State state);
    void setCellColor(const Row::State state, const sf::Color& color);
    void setTextColor(const sf::Color& color);

    std::string getLabel();
    std::string getKey();
    std::function<void()> press;
    std::function<void()> release;

    Action asAction();

private:
    std::pair<sf::RectangleShape, sf::RectangleShape> cells;
    std::pair<sf::Text, sf::Text> labels;

    std::string keyCache; //for resets

    sf::FloatRect bounds;

    State state; //must be initialized through setState() in constructor

    static std::map<State, sf::Color> colors;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
