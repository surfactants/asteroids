#include <input/input_handler.hpp>
#include <system/database.hpp>

Input_Package::Input_Package()
{
    clear();
}

void Input_Package::clear()
{
    keyPressed.clear();
    keyReleased.clear();
    mouse.clear();

    scroll = std::function<void(float)>([](float a) { return; });
}

Input_Handler::Input_Handler(sf::RenderWindow& nwindow, Game& game, UI& ui, Menu_Package menu_package)
    : window { nwindow }
{
    Player* player = &game.getPlayer();

    /////////////////////////////////////////////////////////////
    //GAME AND UI INPUTS
    //
    Input_Package& p_g = context[Main_State::GAME];

    p_g.keyReleased[sf::Keyboard::Escape] = std::bind(&Game::escape, &game);

    std::map<std::string, sf::Keyboard::Key> actions = Database::getActions();

    std::function<void()> uncast = std::bind(&Entity::uncast, player);

    for (const auto& action : actions) {
        std::function<void()> press;
        std::function<void()> release;
        if (action.first == "Move North") {
            press = std::bind(&Player::upStart, player);
            release = std::bind(&Player::upEnd, player);
        }
        else if (action.first == "Move South") {
            press = std::bind(&Player::downStart, player);
            release = std::bind(&Player::downEnd, player);
        }
        else if (action.first == "Move West") {
            press = std::bind(&Player::leftStart, player);
            release = std::bind(&Player::leftEnd, player);
        }
        else if (action.first == "Move East") {
            press = std::bind(&Player::rightStart, player);
            release = std::bind(&Player::rightEnd, player);
        }
        else if (action.first == "Ability 1") {
            press = [player]() { player->castAbility(0); };
            release = uncast;
        }
        else if (action.first == "Ability 2") {
            press = [player]() { player->castAbility(1); };
            release = uncast;
        }
        else if (action.first == "Ability 3") {
            press = [player]() { player->castAbility(2); };
            release = uncast;
        }
        else if (action.first == "Ability 4") {
            press = [player]() { player->castAbility(3); };
            release = uncast;
        }
        p_g.keyPressed[action.second] = std::make_pair(action.first, press);
        p_g.keyReleased[action.second] = release;
    }

    p_g.mouse[Mouse_Event::LEFT_CLICK] = std::bind(&UI::clickLeft, &ui);
    p_g.mouse[Mouse_Event::LEFT_RELEASE] = std::bind(&UI::releaseLeft, &ui);

    p_g.scroll = std::bind(&Game::scroll, &game, std::placeholders::_1);

    p_g.focus_lost = std::bind(&Game::stopInput, &game);

    /////////////////////////////////////////////////////////////
    //MENU INPUTS
    //

    std::map<Menu_State, Menu*> menus = { { Menu_State::MAIN, menu_package.m_main },
        { Menu_State::PAUSE, menu_package.m_pause },
        { Menu_State::SETTINGS, menu_package.m_settings },
        { Menu_State::KEYS, menu_package.m_keymap } };

    for (const auto& m : menus) {
        Input_Package& p = context_menu[m.first];
        p.keyReleased[sf::Keyboard::Escape] = std::bind(&Menu::back, m.second);
        p.mouse[Mouse_Event::LEFT_CLICK] = std::bind(&Menu::clickLeft, m.second);
        p.mouse[Mouse_Event::LEFT_RELEASE] = std::bind(&Menu::releaseLeft, m.second);
        p.scroll = std::bind(&Menu::scroll, m.second, std::placeholders::_1);
        p.focus_lost = std::bind(&Menu::stopInput, m.second);
    }

    context_menu[Menu_State::KEYS].special = std::bind(&Menu_Keymap::keyPressed, menu_package.m_keymap, std::placeholders::_1);
}

const std::vector<Action> Input_Handler::getRemappableActions()
{
    Input_Package& p_g = context[Main_State::GAME];

    std::vector<Action> actions;

    for (size_t k = 0; k < sf::Keyboard::KeyCount; k++) {
        sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(k);
        if (p_g.keyPressed.contains(key)) {
            actions.push_back(Action(p_g.keyPressed[key].first, key, p_g.keyPressed[key].second, p_g.keyReleased[key]));
        }
    }

    return actions;
}

void Input_Handler::setRemappableActions(const std::vector<Action>& actions)
{
    Input_Package& p_g = context[Main_State::GAME];

    Convert_Key converter;

    for (auto k = p_g.keyReleased.begin(); k != p_g.keyReleased.end();) {
        if (k->first != sf::Keyboard::Escape)
            k = p_g.keyReleased.erase(k);
        else
            ++k;
    }

    p_g.keyPressed.clear();

    for (const auto& action : actions) {
        sf::Keyboard::Key k = std::get<sf::Keyboard::Key>(action.key);
        p_g.keyPressed[k].first = action.name;
        p_g.keyPressed[k].second = action.press;
        p_g.keyReleased[k] = action.release;
    }
}

void Input_Handler::handle()
{
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        else {
            if (state_main == Main_State::LOADING
                || state_main == Main_State::NEWGAME
                || state_main == Main_State::NULLSTATE
                || state_main == Main_State::QUIT) {
                continue;
            }

            if (event.type == sf::Event::KeyPressed) {
                if (state_main == Main_State::MENU && state_menu == Menu_State::KEYS) {
                    context[state_main].special(event.key.code);
                }
                else if (context[state_main].keyPressed.count(event.key.code)) {
                    context[state_main].keyPressed[event.key.code].second();
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                if (context[state_main].keyReleased.count(event.key.code)) {
                    context[state_main].keyReleased[event.key.code]();
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && context[state_main].mouse.count(Mouse_Event::LEFT_CLICK)) {
                    context[state_main].mouse[Mouse_Event::LEFT_CLICK]();
                }
                else if (event.mouseButton.button == sf::Mouse::Right && context[state_main].mouse.count(Mouse_Event::RIGHT_CLICK)) {
                    context[state_main].mouse[Mouse_Event::RIGHT_CLICK]();
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (context[state_main].mouse.count(Mouse_Event::LEFT_RELEASE)) {
                        context[state_main].mouse[Mouse_Event::LEFT_RELEASE]();
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    if (context[state_main].mouse.count(Mouse_Event::RIGHT_RELEASE)) {
                        context[state_main].mouse[Mouse_Event::RIGHT_RELEASE]();
                    }
                }
            }
            else if (event.type == sf::Event::MouseWheelScrolled) {
                context[state_main].scroll(event.mouseWheelScroll.delta);
            }
            else if (event.type == sf::Event::LostFocus) {
                context[state_main].focus_lost();
            }
        }
    }
}

void Input_Handler::menuChange()
{
    context[Main_State::MENU].clear();
    context[Main_State::MENU] = context_menu[state_menu];
}
