#include "Game.hpp"

void Game::initVars()
{
    window = nullptr;
    playerInitialPos.x = 12.f;
    playerInitialPos.y = 12.f;
    keyRepeat = true;
}

void Game::initWindow()
{
    videoMode.height = 600;
    videoMode.width = 800;
    window = new sf::RenderWindow(videoMode, "CMake SFML Project");
    window->setFramerateLimit(60);
}

void Game::initPlayer()
{
    try
    {
        player = new Player("Walk.png", playerInitialPos);
        this->player->updatePlayerPositionX(1);
        this->player->updatePlayerPositionY(1);
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

void Game::setKeyRepeat(const bool &status)
{
    window->setKeyRepeatEnabled(status);
    keyRepeat = status;
}

bool const &Game::getKeyRepeat()
{
    return keyRepeat;
}

bool Game::windowIsOpen()
{
    return window->isOpen();
}

void Game::pullEvents()
{
    while (window->pollEvent(gameEvent))
    {
        switch (gameEvent.type)
        {
            case sf::Event::Closed:
                window->close();
            case sf::Event::KeyPressed:
                if (gameEvent.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                    break;
                }
                else if (gameEvent.key.code == sf::Keyboard::D)
                {
                    if (this->player->getPlayerDirection() != RIGHT)
                    {
                        this->player->flipPlayer(RIGHT);
                        this->player->updatePlayerPositionX(-playerInitialPos.x);
                    }
                    this->player->updateSourcePositionX(8);
                    if (this->player->getPlayerSpritePositionX() < 
                    (videoMode.width - this->player->getPlayerSpriteImageWidth() * 1.5f))
                        this->player->updatePlayerPositionX(0.5f);
                }
                else if (gameEvent.key.code == sf::Keyboard::A)
                {
                    this->player->updateSourcePositionX(8);
                    if (this->player->getPlayerDirection() != LEFT)
                    {
                        this->player->flipPlayer(LEFT);
                        this->player->updatePlayerPositionX(playerInitialPos.x);
                    }
                    if (this->player->getPlayerSpritePositionX() >
                    this->player->getPlayerSpriteImageWidth() * 1.5f)
                        this->player->updatePlayerPositionX(-0.5f);
                }
                else if (gameEvent.key.code == sf::Keyboard::W)
                {
                    if (this->player->getPlayerSpritePositionY() >
                    playerInitialPos.y)
                        this->player->updatePlayerPositionY(-0.5f);
                    this->player->updateSourcePositionX(8);
                }
                else if (gameEvent.key.code == sf::Keyboard::S)
                {
                    if (this->player->getPlayerSpritePositionY() <= 
                    (this->videoMode.height - (this->player->getPlayerSpriteImageHeight() * 2.f)))
                        this->player->updatePlayerPositionY(0.5f);
                    this->player->updateSourcePositionX(8);
                }
                else if (gameEvent.key.code == sf::Keyboard::F)
                {
                    this->player->setPlayerTextureFileName("Shot.png");
                    this->player->setPlayerTexture();
                    this->player->updateSourcePositionX(8);
                }
                else if (gameEvent.key.code == sf::Keyboard::Space)
                {
                    setKeyRepeat(false);
                    this->player->setPlayerTextureFileName("Jump.png");
                    this->player->setPlayerTexture();
                    this->player->updateSourcePositionX(8);
                    if (this->player->getPlayerDirection() == RIGHT)
                    {
                        this->player->updatePlayerPositionX(0.5f);
                    }
                    else
                        this->player->updatePlayerPositionX(-0.5f);
                }
                break;
            case sf::Event::KeyReleased:
                if (gameEvent.key.code == sf::Keyboard::F)
                {
                    this->player->setPlayerTextureFileName("Walk.png");
                    this->player->setPlayerTexture();
                }
                if (gameEvent.key.code == sf::Keyboard::Space)
                {
                    this->player->setPlayerTextureFileName("Walk.png");
                    this->player->setPlayerTexture();
                    // window->setKeyRepeatEnabled(true);
                }
            default:
                break;
        }
    }
}

void Game::update()
{
    /*
        @return void

        - Check for game events
        - check for max and min to crop player image correctly and keep action in a loop

        Update game objects
    */
    pullEvents();
    this->player->checkSourcePositionXMax();
    if (this->player->shouldRestSourceXToMax)
        this->player->checkSourcePositionXMin();
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
    std::cout << "player position X = " << this->player->getPlayerSpritePositionX() << std::endl;
    std::cout << "player position Y = " << this->player->getPlayerSpritePositionY() << std::endl;
    std::cout << "player direction = " << this->player->getPlayerDirection() << std::endl;

    while (!keyRepeat && this->player->sourcePosition.x != 73.f)
    {
        this->player->updateSourcePositionX(8);
        this->player->updatePlayerPositionX(0.5f);
        usleep(80000);
        this->player->checkSourcePositionXMax();
        if (this->player->shouldRestSourceXToMax)
            this->player->checkSourcePositionXMin();
        this->player->animatePlayer();
        this->player->render(*window);
        window->display();
        window->clear(sf::Color::Blue);
    }
    setKeyRepeat(true);
    this->player->animatePlayer();
    //Draw here
    this->player->render(*window);

    window->display();
    window->clear(sf::Color::Blue);
}
