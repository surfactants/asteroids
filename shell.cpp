#include "shell.hpp"
#include "primordial.hpp"
#include <iostream>
#include "projectile.hpp"
#include "texture_manager.hpp"

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

    //Texture_Manager::populate();

    Projectile::loadTexture();

    ui.scale(window);

    loadNewLevel();
}

void Shell::run(){
    std::cout << "\nrunning shell...";
    fpsText.setFont(font);
    fpsText.setString("0");
    fpsText.setFillColor(sf::Color::Red);

    sf::Clock fpsClock;

    while(window.isOpen()){
        switch(state){
        case MENU:
            break;
        case LOADING:
            if(loadingScreen.update()){
                game.newLevel();
                state = PLAYING;
            }
            break;
        case PLAYING:
            input();
            update();
            fpsText.setString(std::to_string((int)(1.f / fpsClock.getElapsedTime().asSeconds())));
            fpsClock.restart();
            break;
        }
        draw();
    }
}

void Shell::input(){
    while(window.pollEvent(event)){
        if(event.type == sf::Event::Closed) window.close();
        else{
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close();
            switch(state){
            case MENU:
                break;
            case PLAYING:
                if(!ui.readEvent(event, fMouse())){
                    game.readEvent(event, fMouse(window, viewGame));
                }
                else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                    game.readEvent(event, fMouse(window, viewGame));
                }
                break;
            case LOADING:
                break;
            }
        }
    }
}

void Shell::update(){
    game.update();
    ui.update(game);
}

void Shell::draw(){
    window.clear();
        switch(state){
        case MENU:
            break;
        case PLAYING:
            window.setView(viewGame);
            window.draw(game);
            window.setView(viewUI);
            window.draw(fpsText);
            window.draw(ui);
            break;
        case LOADING:
            window.setView(viewUI);
            window.draw(loadingScreen);
            break;
        }
    window.display();
}

void Shell::loadNewLevel(){
    state = LOADING;
    std::vector<std::function<void()>> loads;
    std::vector<std::string> messages;

    //SKIPPING THE FIRST STEP ALLOWS THE DRAW FUNCTION TO SWAP OVER TO LOADING BEFORE IT BEGINS
        //(MAYBE UNNECESSARY BUT TAKE A LOOK LATER)
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
