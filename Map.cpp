//
// Created by Kayton Fletcher on 3/22/18.
//
#include "Map.h"
#include "SFML/Graphics.hpp"
#include <iostream>

#include <math.h>
void Map::Generate() {
    sf::RenderWindow window(sf::VideoMode(500,500),"Window");
    sf::CircleShape shape(25);
    shape.setPosition(100,100);


    sf::Vector2f velocity;
    int speed = 2;
    double diagonalSpeed = (speed * pow(2,.5))/2;
    while(window.isOpen()) {
        sf::Event event;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            shape.move(diagonalSpeed, -diagonalSpeed);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            shape.move(-diagonalSpeed,-diagonalSpeed);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            shape.move(-diagonalSpeed,diagonalSpeed);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            shape.move(diagonalSpeed, diagonalSpeed);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){

            shape.move(-speed, 0);
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){

            shape.move(speed, 0);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){

            shape.move(0,-speed);
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
          shape.move(0,speed);

        }



        while(window.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

        }
        window.clear();
        window.draw(shape);
        window.display();
    }
}