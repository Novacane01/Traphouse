//
// Created by Kayton Fletcher on 3/22/18.
//
#include "Map.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <math.h>
#include "Player.h"
Map::Map(){}

void Map::Generate() {
    sf::RenderWindow window(sf::VideoMode(500,500),"Window");

    Player player("Donald", 100, 5, 5);

    /* MUST CHANGE SHAPE TO SPRITE AND LOAD TEXTURES APPROPRIATELY*/

    int speed = 2;
    double diagonalSpeed = (speed * pow(2,.5))/2;

    while(window.isOpen()) {
        sf::Event event;

        player.getMovement();

        while(window.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        }
        window.clear();
        //WILL USE GETSPRITE METHOD HERE
        window.draw(player.shape);
        window.display();
    }
}