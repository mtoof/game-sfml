#pragma once

#include "headers.hpp"
#include "Player.hpp"
class Game
{
private:

    sf::RenderWindow* window;
    sf::Event gameEvent;
    Player *player;

    void initVars();
    void initWindow();
    void initPlayer();
public:
    Game();
    virtual ~Game();

    sf::Texture playerTexture;
    sf::Sprite playerSprite;

    //Game objects

    bool windowIsOpen();
    void pullEvents();
    void update();
    void render();
};
