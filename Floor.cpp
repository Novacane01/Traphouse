//
// Created by Kayton Fletcher on 4/19/18.
//

#include "Floor.h"
#include <iostream>
#include <math.h>

Floor::Floor(){
    if (!texture.loadFromFile("Sprites/Map/DungeonFloorStone.png")) {
        std::cout << "Could not load from file" << std::endl;
    }
    floor.setTexture(texture);
}


void Floor::Draw(sf::RenderWindow &window) {
    window.draw(floor);
}