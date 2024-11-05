#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

#include "Player.h"
#include "Enemy.h"
#include "FrameRate.h"
#include "Projectile.h"
#include "Map.h"
#include "MapLoader.h"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "RPG Game", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    Map map;
    map.Initialize();

    Player player;
    player.Initialize();

    Enemy enemy;
    enemy.Initialize();

    FrameRate fps;
    fps.Initialize();

    MapLoader mapLoader;
    mapLoader.Load("assets/world/maps/level1.rmap");

    //LOAD

    map.Load();

    player.Load();

    enemy.Load();

    fps.Load();

    //LOAD
    
    sf::Clock clock;

    //MAIN GAME LOOP
    while (window.isOpen()) 
    {
        sf::Time deltaTimeTimer = clock.restart();
        double deltaTime = deltaTimeTimer.asMicroseconds() / 1000.0f; 

        //UPDATE
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
                window.close();            
        } 

        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));

        map.Update(deltaTime);
        player.Update(deltaTime, enemy, mousePosition);
        enemy.Update(deltaTime);
        fps.Update(deltaTime); 
        //UPDATE
        
        //DRAW
        window.clear(sf::Color::Black);
        
        map.Draw(window);
        enemy.Draw(window);
        player.Draw(window);
        fps.Draw(window);
        window.display();
        //DRAW
    }
    return 0;
}