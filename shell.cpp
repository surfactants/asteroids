#include "shell.hpp"
#include "primordial.hpp"
#include <iostream>
#include "projectile.hpp"
#include "fmouse.hpp"

Shell::Shell()
: window{sf::VideoMode(), "asteroids", sf::Style::Fullscreen}{
    //window.setKeyRepeatEnabled(false);
    sf::Cursor cursor;
    cursor.loadFromSystem(sf::Cursor::Cross);
    window.setMouseCursor(cursor);

    font.loadFromFile("BubblerOne-Regular.ttf");

    viewGame = sf::View(sf::Vector2f(0.f, 0.f), sf::Vector2f(window.getSize()));
    viewGame.setCenter(sf::Vector2f(960.f, 540.f));
    viewGame.zoom(1.5f);

    viewUI.setSize(sf::Vector2f(1920.f, 1080.f));
    viewUI.setCenter(sf::Vector2f(960.f, 540.f));

    viewMenu.setSize(sf::Vector2f(window.getSize()));
    viewMenu.setCenter(sf::Vector2f(window.getSize()) * 0.5f);

    Projectile::loadTexture();

    ui.scale(window);

    alignState();

    std::cout << "\n\n" << state_main << "\t|\t" << state_menu;
}

void Shell::run(){
    std::cout << "\nrunning shell...";
    fpsText.setFont(font);
    fpsText.setString("0");
    fpsText.setFillColor(sf::Color::Red);

    sf::Clock fpsClock;

    while(window.isOpen()){
        switch(state_main){
        case MAIN_NEWGAME:
            loadNewLevel();
            continue;
            break;
        case MAIN_MENU:
            menu->update(fMouse(window, viewUI));
            break;
        case MAIN_LOADING:
            if(loadingScreen.update()){
                game.newLevel();
                state_main = MAIN_GAME;
            }
            break;
        case MAIN_GAME:
            game.update();
            ui.update();
            fpsText.setString(std::to_string((int)(1.f / fpsClock.getElapsedTime().asSeconds())));
            fpsClock.restart();
            break;
        default:
            break;
        }
        input();
        alignState();
        draw();
    }
}

void Shell::input(){
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        else{
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close();
            switch(state_main){
            case MAIN_MENU:
                if(event.type == sf::Event::MouseButtonPressed){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        std::cout << "\nmenu leftclick detected!";
                        menu->click();
                    }
                }
                else if(event.type == sf::Event::MouseButtonReleased){
                    if(event.mouseButton.button == sf::Mouse::Left){
                        menu->unclick();
                    }
                }
                break;
            case MAIN_GAME:
                if(!ui.readEvent(event, fMouse())){
                    game.readEvent(event, fMouse(window, viewGame));
                }
                else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                    game.readEvent(event, fMouse(window, viewGame));
                }
                break;
            case MAIN_LOADING:
                break;
            default:
                break;
            }
        }
    }
}

void Shell::update(){
    switch(state_main){
    case MAIN_MENU:
        menu->update(fMouse(window, viewUI));
        break;
    case MAIN_GAME:
        game.update();
        ui.update();
        break;
    default:
        break;
    }
}

void Shell::draw(){
    window.clear();
        switch(state_main){
        case MAIN_MENU:
            window.setView(viewUI);
            window.draw(*menu);
            break;
        case MAIN_GAME:
            window.setView(viewGame);
            window.draw(game);
            window.setView(viewUI);
            window.draw(fpsText);
            window.draw(ui);
            break;
        case MAIN_LOADING:
            window.setView(viewUI);
            window.draw(loadingScreen);
            break;
        default:
            break;
        }
    window.display();
}

void Shell::loadNewLevel(){
    state_main = MAIN_LOADING;
    std::vector<std::function<void()>> loads;
    std::vector<std::string> messages;

    //SKIPPING THE FIRST STEP ALLOWS THE DRAW FUNCTION TO SWAP OVER TO LOADING BEFORE IT BEGINS
    loads.push_back(std::function<void()>([]{ return; }));
        messages.push_back("pee");

    loads.push_back(std::bind(&World::makeFloor, &game.getWorld()));
        messages.push_back("carving rooms...");

    loads.push_back(std::bind(&World::makeWalls, &game.getWorld()));
        messages.push_back("reinforcing structures...");

    loads.push_back(std::bind(&Game::spawnEnemies, &game));
        messages.push_back("reticulating splines...");

    loadingScreen.prepare(loads, messages);
}

void Shell::alignState(){
    if(change_main){
        change_main = false;
        switch(state_main){
        case MAIN_QUIT:
            window.close();
            break;
        case MAIN_NEWGAME:
            loadNewLevel();
            break;
        default:
            break;
        }
    }
    if(change_menu){
        change_menu = false;
        switch(state_menu){
        case MENU_MAIN:
            menu = &menu_main;
            break;
        case MENU_PAUSE:
            menu = &menu_pause;
            break;
        case MENU_SETTINGS:
            menu = &menu_settings;
            break;
        default:
            break;
        }
    }
}
