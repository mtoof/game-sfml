#pragma once


#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <memory>
#include <thread>

class Game
{
private:

    std::shared_ptr<sf::RenderWindow> window;
    std::shared_ptr<Player> player;
    sf::Event gameEvent;
    sf::Vector2f playerInitialPos;
    void initVars();
    void initWindow();
    void initPlayer();
    bool keyRepeat;
    void handleSpace();
    bool isJumping;
    bool isSpacePressed;
public:
    std::shared_ptr<std::thread> jump;
    Game();
    virtual ~Game();
    sf::VideoMode videoMode;

    void setKeyRepeat(const bool &status);
    bool const &getKeyRepeat();
    //Game objects
    bool const &getIsJumping();
    bool windowIsOpen();
    void pullEvents();
    void update();
    void render();
};
