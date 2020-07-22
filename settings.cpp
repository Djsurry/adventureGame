#include "settings.h"
int numberOfTextures = 3;
int numberOfItems = 2;
int windowWidth = 1700;
int windowHeight = 1500;
int tileWidth = 100;
int XVisibleTiles = windowWidth/tileWidth;
int YVisibleTiles = windowHeight/tileWidth;
int CENTER_SQURE_X = (int)floor((float)XVisibleTiles/2)*tileWidth;
int CENTER_SQURE_Y = (int)floor((float)YVisibleTiles/2)*tileWidth;

