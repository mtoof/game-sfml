// #pragma once

#include "headers.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Player {
    private:

    int imageHeight, imageWidth;
    int increaseX;
    
    std::string playerTextureFileName;
    sf::Sprite playerSprite;

    sf::Vector2i playerPosition;
    sf::Texture playerTexture;
    sf::Vector2i sourcePosition;
    

    public:
        Player(std::string textureFileName);
        virtual ~Player();

        void initVariables();
        void checkPositionX();
        void updateSourcePositionX(int size);
        void setPlayerSprite();
        void setPlayerTexture();
        void setPlayerTextureFileName(std::string fileName);
        void setTextureX();
        void setTextureY();
        void animatePlayer();
        void update();
        void render(sf::RenderTarget &target);
};