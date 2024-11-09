#pragma once


#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

class Game
{
private:

    sf::RenderWindow* window;
    sf::Event gameEvent;
    Player *player;
    sf::Vector2f playerInitialPos;
    void initVars();
    void initWindow();
    void initPlayer();
    bool keyRepeat;
public:
    Game();
    virtual ~Game();
    sf::VideoMode videoMode;
    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    void setKeyRepeat(const bool &status);
    bool const &getKeyRepeat();
    //Game objects

    bool windowIsOpen();
    void pullEvents();
    void update();
    void render();
};
