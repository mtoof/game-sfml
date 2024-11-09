#include "Player.hpp"

Player::Player(std::string textureFileName, sf::Vector2f &position): playerTextureFileName(textureFileName)
{
    initVariables();
    playerPosition.x  = position.x;
    playerPosition.y = position.y;
    setPlayerTexture();
    setPlayerSprite();
    update();
}

Player::~Player()
{
}

void Player::initVariables()
{
    sourcePosition.x = 1.f;
    sourcePosition.y = 50.f;
    shouldRestSourceXToMax = false;
    imageHeight = 80;
    imageWidth = 90;
    increaseX = 16;
    playerDirection = RIGHT;
}


void Player::setPlayerTexture()
{
    if (!playerTexture.loadFromFile("../src/texture/Gangster/" + playerTextureFileName))
        throw std::runtime_error("Player::setPlayerTexture::Could not load player " + playerTextureFileName + " texture");
}

void Player::setPlayerTextureFileName(std::string fileName)
{
    playerTextureFileName = fileName;
}

void Player::setPlayerSprite()
{
    playerSprite.setTexture(playerTexture);
}

void Player::update()
{
    playerSprite.setScale({1.5f, 1.5f});
}

void Player::render(sf::RenderTarget &target)
{
    target.draw(playerSprite);
}

void Player::animatePlayer()
{
    playerSprite.setTextureRect(sf::IntRect(sourcePosition.x * increaseX, sourcePosition.y, imageWidth, imageHeight));
}

void Player::reverseAnimatePlayer()
{
    playerSprite.setTextureRect(sf::IntRect(sourcePosition.x * (-increaseX), sourcePosition.y, imageWidth, imageHeight));
}


void Player::checkSourcePositionXMax()
{
    if (sourcePosition.x * increaseX >= playerTexture.getSize().x)
        sourcePosition.x = 1.f;
}

void Player::checkSourcePositionXMin()
{
    if (sourcePosition.x <= 1.f && shouldRestSourceXToMax)
    {
        sourcePosition.x = 73;
        shouldRestSourceXToMax = false;
    }
}

const float Player::getPlayerSpritePositionX()
{
    return playerSprite.getPosition().x;
}

const float Player::getPlayerSpritePositionY()
{
    return playerSprite.getPosition().y;
}

const float Player::getPlayerSpriteImageWidth()
{
    return imageWidth;
}

const float Player::getPlayerSpriteImageHeight()
{
    return imageHeight;
}

const int Player::getPlayerDirection()
{
    return playerDirection;
}

void Player::flipPlayer(int direction)
{
    sf::Vector2f currentScale = playerSprite.getScale();
    if (direction == LEFT)
    {
        playerSprite.setScale(-currentScale.x, currentScale.y);
        playerDirection = LEFT;
    }
    else if (direction == RIGHT)
    {
        playerSprite.setScale(currentScale.x * (-1), currentScale.y);
        playerDirection = RIGHT;
    }
}

void Player::updateSourcePositionX(float size)
{
    if ((sourcePosition.x + size) >= 0)
        sourcePosition.x += size;
    if ((size <= 0 && (sourcePosition.x <= 1.f)))
        shouldRestSourceXToMax = true;
}

void Player::updatePlayerPositionX(float size)
{
    playerSprite.move(playerPosition.x * size, 0);
}

void Player::updatePlayerPositionY(float size)
{
    playerSprite.move(0, playerPosition.y * size);
}