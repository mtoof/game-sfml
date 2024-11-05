#include "Player.hpp"

Player::Player(std::string textureFileName, sf::Vector2f &position): playerTextureFileName(textureFileName)
{
    this->initVariables();
    playerPosition.x  = position.x;
    playerPosition.y = position.y;
    this->setPlayerTexture();
    this->setPlayerSprite();
}

Player::~Player()
{
}

void Player::initVariables()
{
    this->sourcePosition.x = 1.f;
    this->sourcePosition.y = 50.f;
    shouldRestSourceXToMax = false;
    this->imageHeight = 80;
    this->imageWidth = 90;
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


void Player::checkSourcePositionX()
{
    if (this->sourcePosition.x * increaseX >= this->playerTexture.getSize().x)
        this->sourcePosition.x = 1.f;
}

void Player::resetSourcePositionX()
{
    if (this->sourcePosition.x <= 1.f)
        this->sourcePosition.x = (4 * 8);
}

void Player::updateSourcePositionX(float size)
{
    if ((this->sourcePosition.x + size) >= 0)
        this->sourcePosition.x += size;
    if ((size <= 0 && (this->sourcePosition.x <= 1.f)))
        shouldRestSourceXToMax = true;
}

void Player::updatePlayerPositionY(float size)
{
    this->playerSprite.move(this->playerPosition.x, this->playerPosition.y * size);
    this->playerPosition.y += size;
}

void Player::updatePlayerPositionX(float size)
{
    this->playerSprite.move(this->playerPosition.x * size, 0);
    this->playerPosition.x += size;
}