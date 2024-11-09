#include "headers.hpp"

int main()
{
    Game game;
    
    while (game.windowIsOpen())
    {
        game.update();
        game.render();
    }
}
