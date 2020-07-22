#include "Hero.h"

Hero::Hero()
{
    x = 0.f;
    y = 0.f;
}

Hero::~Hero()
{

}

void Hero::draw(sf::RenderWindow * window, sf::Texture textures[numberOfTextures])
{
    sf::RectangleShape rectangle(sf::Vector2f((float)tileWidth, (float)tileWidth));
    rectangle.setTexture(&textures[2]);
    rectangle.setPosition((float)CENTER_SQURE_X, (float)CENTER_SQURE_Y);
    window->draw(rectangle);
}


