// #include "Enemy.h"
#include "settings.h"
#include "Hero.h"
struct Item
{
    int id;
    std::string name;
    int attack_damage;
    float range;
    int cost;
};
/*

COMPILE ON MAC: clang++ main.cpp -lsfml-graphics  -lsfml-window -lsfml-system

*/
// settings
/*
int numberOfTextures = 3;
int numberOfItems = 2;
int windowWidth = 1700;
int windowHeight = 1500;
int tileWidth = 100;
int XVisibleTiles = windowWidth/tileWidth;
int YVisibleTiles = windowHeight/tileWidth;
const int CENTER_SQURE_X = (int)floor((float)XVisibleTiles/2)*tileWidth;
const int CENTER_SQURE_Y = (int)floor((float)YVisibleTiles/2)*tileWidth;
*/


std::string load_map(std::string filename, int* width, int* height)
{
    std::ifstream myfile;
    std::string wchar;
    std::string hchar;
    myfile.open(filename);
    // Each of these loops reads byte by byte until they reach |, as that character is used to seperate
    // the width and height from the body of the map
    while (true)
    {
        char w[1];
        myfile.read(w, 1);
        if (*w != '|')
        {   
            wchar.append(std::string(1, *w));
        } else {
            break;
        }

    }
    while (true)
    {
        char h[1];
        myfile.read(h, 1);
        if (*h != '|')
        {   
            hchar.append(std::string(1, *h));
        } else {
            break;
        }

    }
    // The width and height of the map are converted to integers
    *width = atoi(wchar.c_str()); 
    *height = atoi(hchar.c_str());
    // Allocates memory for the rest of the map
    char * maparray = (char*)malloc(*height * *width * 2 + 1);
    myfile.read(maparray, *height * *width * 2 +1);
    myfile.close();
    // converts map to c++ string and then frees the memory that was used for c string
    std::string mapstring = maparray;
    free(maparray);
    return mapstring;
}

void draw_map(sf::RenderWindow * window, sf::Texture textures[numberOfTextures], char** maparray, int width, int height, float x, float y)
{
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            float xoffset = x-i;
            float yoffset = y-j;
            if (xoffset > XVisibleTiles || yoffset > YVisibleTiles)
            {
                continue;
            }
            sf::RectangleShape rectangle(sf::Vector2f((float)tileWidth, (float)tileWidth));
           
            switch ((char)maparray[i][j])
            {
                case 'g': 
                    rectangle.setTexture(&textures[0]);
                    break;
                case 't':
                    rectangle.setTexture(&textures[1]);
                    break;
                default:
                    rectangle.setFillColor(sf::Color(0, 0, 0));
                    break;

            }
              
            rectangle.setPosition((float)CENTER_SQURE_X-xoffset*tileWidth, (float)CENTER_SQURE_Y-yoffset*tileWidth);
            window->draw(rectangle);
        }
    }

}

void draw_char(sf::RenderWindow * window, sf::Texture textures[numberOfTextures])
{
    sf::RectangleShape rectangle(sf::Vector2f((float)tileWidth, (float)tileWidth));
    rectangle.setTexture(&textures[2]);
    rectangle.setPosition((float)CENTER_SQURE_X, (float)CENTER_SQURE_Y);
    window->draw(rectangle);
}

void update_pos(float* x, float* y, float acc, int width, int height, bool** solidarray)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        *x -= acc;
        // Handles borders
        if (*x < 0)
        {
            *x = 0;
        }
        // Collision with solid tiles
        if (floor(*y) == *y)
        {
            if (solidarray[(int)floor(*x)][(int)floor(*y)] == true)
            {
                *x = ceil(*x);
            }
        } 
        else 
        {   
            if (solidarray[(int)floor(*x)][(int)floor(*y)] == true || solidarray[(int)floor(*x)][(int)ceil(*y)] )
            {
                *x = ceil(*x);
            }
        }
        return;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        *x += acc;
        // Handles borders
        if (*x + 1 > width)
        {
            *x = width - 1;
        }
        // Collision with solid tiles
        if (floor(*y) == *y)
        { 
            if (solidarray[(int)floor(*x+1)][(int)floor(*y)] == true)
            {
                *x = floor(*x);
            }
        } 
        else 
        {
            if (solidarray[(int)floor(*x+1)][(int)floor(*y)] == true || solidarray[(int)floor(*x+1)][(int)ceil(*y)] )
            {
                *x = floor(*x);
            }
        }
        return;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        *y -= acc;
        // Handles borders
        if (*y < 0)
        {
            *y = 0;
        }
        // Collision with solid tiles
        if (floor(*x) == *x)
        {    
            if (solidarray[(int)floor(*x)][(int)floor(*y)] == true)
            {
                *y = ceil(*y);
            }     
        } 
        else 
        {
            if (solidarray[(int)floor(*x)][(int)floor(*y)] == true || solidarray[(int)ceil(*x)][(int)floor(*y)] )
            {
                *y = ceil(*y);
            } 
        }
        return;
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        *y += acc;
        // Handles borders
        if (*y + 1 > height)
        {
            *y = height - 1;
        }
        // Collision with solid tiles
        if (floor(*x) == *x)
        {
            
            if (solidarray[(int)floor(*x)][(int)floor(*y+1)] == true)
            {
                *y = floor(*y);
            }
        } 
        else 
        {
            if (solidarray[(int)floor(*x)][(int)floor(*y+1)] == true || solidarray[(int)ceil(*x)][(int)floor(*y+1)] )
            {
                *y = floor(*y);
            }
        
        }
        return;
    } 
}

void generate_items(Item * item_list)
{  
    // gen fist
    Item fist;
    fist.id = 1;
    fist.name = "Fists";
    fist.attack_damage = 10;
    fist.range = 0.1f;
    fist.cost = 10;
    item_list[0] = fist;
}


int main()
{   
    Item * item_list;
    item_list = (Item*)malloc(numberOfItems*sizeof(Item));
    generate_items(item_list);
    // Init map
    int map_width;
    int map_height;
    std::string m = load_map("map", &map_width, &map_height);
    std::string solidstring = m.substr(m.find(" ")+1, std::string::npos);
    std::string mapstring = m.substr(0, m.find(" "));
    char** maparray;
    bool** solidarray;
    solidarray = new bool *[map_width];
    maparray = new char *[map_width];

    for(size_t i = 0; i <map_width; i++)
    {
        maparray[i] = new char[map_height];
    }
    for(size_t i = 0; i <map_width; i++)
    {
        solidarray[i] = new bool[map_height];
    }
    {
        int x = 0;
        int y = 0;
        for (size_t i = 0; i < mapstring.length(); i++)
        {
            maparray[x][y] = mapstring[i];
            x++;
            if (x==map_width)
            {
                x=0;
                y++;
            }
        }
    }  
    {
        int x = 0;
        int y = 0;
        for (size_t i = 0; i < solidstring.length(); i++)
        {
            if (solidstring[i] == 't'){
                solidarray[x][y] = true;
            } else {
                solidarray[x][y] = false;
            }
            x++;
            if (x==map_width)
            {
                x=0;
                y++;
            }
        }
    }
    
    // load textures
    sf::Texture textures[numberOfTextures];
    sf::Texture grass_texture;
    if (!grass_texture.loadFromFile("grasstexture.png"))
    {
        std::cout << "Error loading texture. Couldn't load grasstexture.png \n";
        exit(1);
    }
    textures[0] = grass_texture;
    sf::Texture tree_texture;
    if (!tree_texture.loadFromFile("treetexture.jpg"))
    {
        std::cout << "Error loading texture. Couldn't load treetexture.jpg \n";
        exit(1);
    }
    textures[1] = tree_texture;
    sf::Texture char_texture;
    if (!char_texture.loadFromFile("champtexture.png"))
    {
        std::cout << "Error loading texture. Couldn't load champtexture.png \n";
        exit(1);
    }
    textures[2] = char_texture;
    // init Hero
    Hero hero;
    // create the window
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Awesome game");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
            {
                free(item_list);
                window.close();
            }
        }

        update_pos(&hero.x, &hero.y, 0.01f, map_width, map_height, solidarray);
        // clear the window with black color
        window.clear(sf::Color::Black);

        draw_map(&window, textures, maparray, map_width, map_height, hero.x, hero.y);
        draw_char(&window, textures);

        // end the current frame
        window.display();
    }

    return 0;
}
