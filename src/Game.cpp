#include "Game.hpp"

void Game::initVars()
{
    window = nullptr;
    playerInitialPos.x = 12.f;
    playerInitialPos.y = 12.f;
    isJumping = false;
    isSpacePressed = false;
}

void Game::initWindow()
{
    videoMode.height = 600;
    videoMode.width = 800;
    window = std::make_shared<sf::RenderWindow>(videoMode, "CMake SFML Project");
    window->setFramerateLimit(60);
    setKeyRepeat(true);
}

void Game::initPlayer()
{
    try
    {
        player = std::make_shared<Player>("Walk.png", playerInitialPos);
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

bool const &Game::getIsJumping()
{
    return isJumping;
}

bool Game::windowIsOpen()
{
    return window->isOpen();
}

void Game::handleSpace(){
    setKeyRepeat(false);
    this->player->setPlayerTextureFileName("Jump.png");
    this->player->setPlayerTexture();
    this->player->updateSourcePositionX(8.f);
    while (this->player->sourcePosition.x <= 73.f && !keyRepeat)
    {
        update();
        render();
        this->player->updateSourcePositionX(8.f);
        if (this->player->getPlayerDirection() == RIGHT && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (this->player->getPlayerSpritePositionX() < 
            (videoMode.width - this->player->getPlayerSpriteImageWidth() * 1.5f))
                this->player->updatePlayerPositionX(0.5f);
        }
        else if (this->player->getPlayerDirection() == LEFT && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (this->player->getPlayerSpritePositionX() >
            this->player->getPlayerSpriteImageWidth() * 1.5f)
                this->player->updatePlayerPositionX(-0.5f);
        }
        usleep(80000);
    }
    this->player->setPlayerTextureFileName("Walk.png");
    this->player->setPlayerTexture();
    isJumping = false;
    return;
}


void Game::pullEvents()
{
    bool isDPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool isAPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
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
                else if (gameEvent.key.code == sf::Keyboard::W)
                {
                    if (!keyRepeat)
                        setKeyRepeat(true);
                    if (this->player->getPlayerSpritePositionY() >
                    playerInitialPos.y)
                        this->player->updatePlayerPositionY(-0.5f);
                    this->player->updateSourcePositionX(8.f);
                }
                else if (gameEvent.key.code == sf::Keyboard::S)
                {
                    if (!keyRepeat)
                        setKeyRepeat(true);
                    if (this->player->getPlayerSpritePositionY() <= 
                    (this->videoMode.height - (this->player->getPlayerSpriteImageHeight() * 2.f)))
                        this->player->updatePlayerPositionY(0.5f);
                    this->player->updateSourcePositionX(8.f);
                }
                else if (gameEvent.key.code == sf::Keyboard::F)
                {
                    if (!keyRepeat)
                        setKeyRepeat(true);
                    this->player->setPlayerTextureFileName("Shot.png");
                    this->player->setPlayerTexture();
                    this->player->updateSourcePositionX(8.f);
                }
                else if (gameEvent.key.code == sf::Keyboard::Space)
                {
                    setKeyRepeat(false);
                    isJumping = true;
                    jump = std::make_shared<std::thread> (&Game::handleSpace, this);
                    jump->join();
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
                    setKeyRepeat(false);
                    isSpacePressed = false;
                }
                break;
            default:
                break;
        }
    }
    if (isDPressed && !isJumping)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            if (!keyRepeat)
                setKeyRepeat(true);
            this->player->setPlayerTextureFileName("Shot.png");
            this->player->setPlayerTexture();
            this->player->updateSourcePositionX(8.f);
            usleep(50000);
            return;
        }
        setKeyRepeat(false);

        this->player->setPlayerTextureFileName("Walk.png");
        this->player->setPlayerTexture();
        if (this->player->getPlayerDirection() != RIGHT)
        {
            this->player->flipPlayer(RIGHT);
            this->player->updatePlayerPositionX(-playerInitialPos.x);
        }
        this->player->updateSourcePositionX(8.f);
        if (this->player->getPlayerSpritePositionX() < 
        (videoMode.width - this->player->getPlayerSpriteImageWidth() * 1.5f))
            this->player->updatePlayerPositionX(0.5f);
        usleep(50000);
    }
    else if (isAPressed && !isJumping)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        {
            if (!keyRepeat)
                setKeyRepeat(true);
            this->player->setPlayerTextureFileName("Shot.png");
            this->player->setPlayerTexture();
            this->player->updateSourcePositionX(8.f);
            usleep(50000);
            return;
        }
        setKeyRepeat(false);
        this->player->setPlayerTextureFileName("Walk.png");
        this->player->setPlayerTexture();
        this->player->updateSourcePositionX(8.f);
        if (this->player->getPlayerDirection() != LEFT)
        {
            this->player->flipPlayer(LEFT);
            this->player->updatePlayerPositionX(playerInitialPos.x);
        }
        if (this->player->getPlayerSpritePositionX() >
        this->player->getPlayerSpriteImageWidth() * 1.5f)
            this->player->updatePlayerPositionX(-0.5f);
        usleep(50000);
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

    this->player->animatePlayer();
    //Draw here
    this->player->render(*window);

    window->display();
    window->clear(sf::Color::Blue);
}
