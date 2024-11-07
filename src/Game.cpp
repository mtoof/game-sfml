#include "Game.hpp"
#include "unistd.h"

void Game::initVars()
{
    this->window = nullptr;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;
    window = new sf::RenderWindow(videoMode, "CMake SFML Project");
    this->window->setFramerateLimit(60);
}

void Game::initPlayer()
{
    try
    {
        sf::Vector2f vecPos;
        vecPos.x = 12.f;
        vecPos.y = 12.f;
        player = new Player("Walk.png", vecPos);
        player->updatePlayerPositionX(1);
        player->updatePlayerPositionY(1);
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
            case sf::Event::KeyPressed:
                if (this->gameEvent.key.code == sf::Keyboard::Escape)
                {
                    this->window->close();
                    break;
                }
                else if (this->gameEvent.key.code == sf::Keyboard::D)
                {
                    this->player->updateSourcePositionX(8);
                    if (this->player->playerSprite.getPosition().x < 720.50f)
                        this->player->updatePlayerPositionX(0.5f);
                }
                else if (this->gameEvent.key.code == sf::Keyboard::A)
                {
                    this->player->updateSourcePositionX(-8);
                    if (this->player->playerSprite.getPosition().x > 12.5f)
                        this->player->updatePlayerPositionX(-0.5f);
                }
                else if (this->gameEvent.key.code == sf::Keyboard::W)
                {
                    if (this->player->playerSprite.getPosition().y > 12.5f)
                        this->player->updatePlayerPositionY(-0.5f);
                    this->player->updateSourcePositionX(8);
                }
                else if (this->gameEvent.key.code == sf::Keyboard::S)
                {
                    if (this->player->playerSprite.getPosition().y <= 500.f)
                        this->player->updatePlayerPositionY(0.5f);
                    this->player->updateSourcePositionX(8);
                }
                break;
            default:
                break;
        }
    }
}

void Game::update()
{
    pullEvents();
    this->player->checkSourcePositionX();
    if (this->player->shouldRestSourceXToMax)
        this->player->resetSourcePositionX();
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

    std::cout << "source position X = " << this->player->sourcePosition.x << std::endl;
    std::cout << "source position Y = " << this->player->sourcePosition.y << std::endl;
    std::cout << "player position X = " << this->player->playerSprite.getPosition().x << std::endl;
    std::cout << "player position Y = " << this->player->playerSprite.getPosition().y << std::endl;
    this->player->animatePlayer();

    //Draw here
    this->player->render(*this->window);

    this->window->display();
    this->window->clear(sf::Color::Blue);
}
