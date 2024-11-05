#include "Game.hpp"
#include "unistd.h"

void Game::initVars()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    window = new sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    this->window->setFramerateLimit(60);
}

void Game::initPlayer()
{
    try
    {
        player = new Player("Walk.png");
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}

Game::Game()
{
    initVars();
    initWindow();
    initPlayer();
}

Game::~Game()
{
    delete window;
    delete player;
}

bool Game::windowIsOpen()
{
    return window->isOpen();
}

void Game::pullEvents()
{
    while (this->window->pollEvent(this->gameEvent))
    {
        switch (this->gameEvent.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->gameEvent.key.code == sf::Keyboard::Escape)
                    this->window->close();
                else if (this->gameEvent.key.code == sf::Keyboard::D)
                    this->player->updateSourcePositionX(8);
                else if (this->gameEvent.key.code == sf::Keyboard::A)
                    this->player->updateSourcePositionX(-8);
                break;
        }
    }
}

void Game::update()
{
    pullEvents();
    this->player->checkPositionX();
}

void Game::render()
{
    /*
        @return void

        - clear old frame
        - render objects
        - display frame in window

        Renders the game objects
    */

   this->player->animatePlayer();

    //Draw here
    this->window->clear();

    this->player->render(*this->window);

    this->window->display();
}
