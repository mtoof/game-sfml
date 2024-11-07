// #pragma once

#include "headers.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player {
    private:

    int imageHeight, imageWidth;
    int increaseX;
    
    std::string playerTextureFileName;

    

    public:
        Player(std::string textureFileName, sf::Vector2f &position);
        virtual ~Player();
        sf::Texture playerTexture;
        sf::Sprite playerSprite;

        bool shouldRestSourceXToMax;

        sf::Vector2f sourcePosition;
        sf::Vector2f playerPosition;
        void initVariables();
        void checkSourcePositionX();
        void resetSourcePositionX();

        void setPlayerSprite();
        void setPlayerTexture();
        void setPlayerTextureFileName(std::string fileName);

        void updatePlayerPositionY(float size);
        void updatePlayerPositionX(float size);

        void setTextureX();
        void setTextureY();
        void updateSourcePositionX(float size);

        void animatePlayer();

        void update();
        void render(sf::RenderTarget &target);
};