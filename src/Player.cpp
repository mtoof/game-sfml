#include "Player.hpp"

Player::Player(std::string textureFileName): playerTextureFileName(textureFileName)
{
    this->initVariables();
    this->setPlayerTexture();
    this->setPlayerSprite();
}

Player::~Player()
{
}

void Player::initVariables()
{
    this->sourcePosition.x = 1;
    this->sourcePosition.y = 50;
    this->playerPosition.x = 1;
    this->playerPosition.y = 1;
    this->imageHeight = 90;
    this->imageWidth = 125;
    increaseX = 16;
}

void Player::setPlayerTexture()
{
    if (!this->playerTexture.loadFromFile("../src/texture/Gangster/" + playerTextureFileName))
        throw std::runtime_error("Player::setPlayerTexture::Could not load player texture");
}

void Player::setPlayerTextureFileName(std::string fileName)
{
    this->playerTextureFileName = fileName;
}

void Player::setPlayerSprite()
{
    this->playerSprite.setTexture(this->playerTexture);
}

void Player::update()
{
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(this->playerSprite);
}

void Player::animatePlayer()
{
    this->playerSprite.setTextureRect(sf::IntRect(this->sourcePosition.x * increaseX, this->sourcePosition.y, imageWidth, imageHeight));
}


void Player::checkPositionX()
{
    if (this->sourcePosition.x * increaseX >= this->playerTexture.getSize().x)
        this->sourcePosition.x = 1;
}

void Player::updateSourcePositionX(int size)
{
    this->sourcePosition.x += size;
}
