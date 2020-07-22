#ifndef Hero_h
#define Hero_h
#include "settings.h"
class Hero
{
private:
    char dir;
public:
    float x;
    float y;
    Hero();    //Constructor prototype
    ~Hero();   //Destructor prototype
    //void draw(sf::RenderWindow * window, sf::Texture textures[numberOfTextures]);
};
#endif