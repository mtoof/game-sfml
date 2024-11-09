#pragma once

#include <SFML/Graphics.hpp>

enum Direction {LEFT, RIGHT};

class Player {
    private:

        float imageHeight, imageWidth;
        int increaseX;

        std::string playerTextureFileName;
        sf::Vector2f playerPosition;
        sf::Sprite playerSprite;
        int playerDirection;

    public:
        Player(std::string textureFileName, sf::Vector2f &position);
        virtual ~Player();
        sf::Texture playerTexture;

        bool shouldRestSourceXToMax;

        sf::Vector2f sourcePosition;

        void initVariables();
        void checkSourcePositionXMax();
        void checkSourcePositionXMin();
        void setPlayerSprite();
        void setPlayerTexture();
        void setPlayerTextureFileName(std::string fileName);

        void updatePlayerPositionY(float size);
        void updatePlayerPositionX(float size);

        void setTextureX();
        void setTextureY();
        void flipPlayer(int direction);
        void updateSourcePositionX(float size);

        void animatePlayer();
        void reverseAnimatePlayer();

        std::string const &getPlayerTextureFileName();
        const float getPlayerSpritePositionX();
        const float getPlayerSpritePositionY();
        const float getPlayerSpriteImageWidth();
        const float getPlayerSpriteImageHeight();
        const int   getPlayerDirection();

        void update();
        void render(sf::RenderTarget &target);
};