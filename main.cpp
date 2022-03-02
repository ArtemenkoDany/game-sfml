#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "map.h"
#include "view.h"

using namespace sf;
using namespace std;

class Player
{
    private:
        float x, y = 0;
    
    public:
        float w, h, dx, dy, speed = 0;
        int dir = 0, playScore = 0, health = 0;
        bool life;
        String File;
        Image image;
        Texture texture;
        Sprite sprite;
    

        Player(String F, float X, float Y, float W, float H)
        {
            dir = 0; playScore = 0; health = 100;
            life = true;
            dx=0;dy=0;speed=0;dir=0;
            File = F;
            w = W; h = H;
            image.loadFromFile(File);
            image.createMaskFromColor(Color(41, 33, 59));
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            x = X; y = Y;
            sprite.setTextureRect(IntRect(0, 0, w, h));
        }
        void update(float time)
        {
            switch (dir)
            {
                case 0: dx = speed; dy = 0; break;
                case 1: dx = -speed; dy = 0; break;
                case 2: dx = 0; dy = speed; break;
                case 3: dx = 0; dy = -speed; break;
            }
            x += dx*time;
            y += dy*time;
        
            speed = 0;
            sprite.setPosition(x,y);
            interactionWithMap();
            if (health <= 0){life = false;}
        }
    float GetPlayerCoordinatX()
    {
        return x;
    }
    float GetPlayerCoordinatY()
    {
        return y;
    }
    
    void interactionWithMap()
    {
        for (int i = y / 32; i < (y + h) / 32; i++)
            for (int j = x / 32; j<(x + w) / 32; j++)
            {
                if (TileMap[i][j] == '0')
                {
                    if (dy>0)
                    {
                        y = i * 32 - h;
                    }
                    if (dy<0)
                    {
                        y = i * 32 + 32;
                    }
                    if (dx>0)
                    {
                        x = j * 32 - w;
                    }
                    if (dx < 0)
                    {
                        x = j * 32 + 32;
                    }
                }
     
                if (TileMap[i][j] == 's')
                {
                    playScore++;
                    TileMap[i][j] = ' ';
                }
                if (TileMap[i][j] == 'f')
                {
                    health -=40;
                    TileMap[i][j] = ' ';
                }
                if (TileMap[i][j] == 'h')
                {
                    health+=20;
                    TileMap[i][j] = ' ';
                }

            }
    }
};


    
    
    
int main()
    {
    RenderWindow window(sf::VideoMode(1080, 720), "Game");
    view.reset(FloatRect(0, 0, 1080, 720));
        
    Font font;
    font.loadFromFile("/Users/user/Desktop/c++/SFML Tut/SFML Tut/2303.ttf");
    Text text("",font, 20);
    text.setColor(Color::Red);
    text.setStyle(Text::Bold);

    Image map_image;
    map_image.loadFromFile("/Users/user/Desktop/c++/SFML Tut/Sprites/map.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(map);
    
    Player p("/Users/user/Desktop/c++/SFML Tut/Sprites/1.png", 250, 250, 96.0, 96.0);

    float CurrentFrame = 0;
    Clock clock;
    Clock gameTimeclock;
    int gameTime = 0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        
        if(p.life) gameTime = gameTimeclock.getElapsedTime().asSeconds();
        clock.restart();
        time = time/800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
    if(p.life == true)
    {
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            p.dir = 1; p.speed = 0.1;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96));
            GetPlayerCoordinateForView(p.GetPlayerCoordinatX(), p.GetPlayerCoordinatY());
        }
        if(Keyboard::isKeyPressed(Keyboard::D))
        {
            p.dir = 0; p.speed = 0.1;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));
            GetPlayerCoordinateForView(p.GetPlayerCoordinatX(), p.GetPlayerCoordinatY());
        }
        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            p.dir = 3; p.speed = 0.1;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));
            GetPlayerCoordinateForView(p.GetPlayerCoordinatX(), p.GetPlayerCoordinatY());
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            p.dir = 2; p.speed = 0.1;
            CurrentFrame += 0.005*time;
            if (CurrentFrame > 3) CurrentFrame -= 3;
                p.sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
        }
    }
        GetPlayerCoordinateForView(p.GetPlayerCoordinatX(), p.GetPlayerCoordinatY());
        p.update(time);
        
        window.setView(view);
        window.clear();
        for (int i = 0; i < HEIGHT_MAP; i++)
                for (int j = 0; j < WIDTH_MAP; j++)
                {
                    if (TileMap[i][j] == ' ')
                        s_map.setTextureRect(IntRect(0, 0, 32, 32));
                    if (TileMap[i][j] == 's')
                        s_map.setTextureRect(IntRect(32, 0, 32, 32));
                    if ((TileMap[i][j] == '0'))
                        s_map.setTextureRect(IntRect(64, 0, 32, 32));
                    if((TileMap[i][j] == 'f'))
                        s_map.setTextureRect(IntRect(96, 0, 32, 32));
                    if((TileMap[i][j] == 'h'))
                        s_map.setTextureRect(IntRect(128, 0, 32, 32));
                    s_map.setPosition(j * 32, i * 32);
                    window.draw(s_map);
                }
        ostringstream playerScoreString;
        ostringstream playerHealthString;
        playerScoreString << p.playScore; playerHealthString << p.health;
        text.setString("Romas heads colected: " + playerScoreString.str() +"\nHealth: " + playerHealthString.str() + " " );
        text.setPosition(view.getCenter().x-520, view.getCenter().y-350);
        window.draw(text);
        
        ostringstream gameTimeString;
        gameTimeString << gameTime;
        text.setString("Time: " + gameTimeString.str() );
        text.setPosition(view.getCenter().x+450, view.getCenter().y-350);
        window.draw(text);
        
        window.draw(p.sprite);
        window.display();
    }
    return 0;
}

