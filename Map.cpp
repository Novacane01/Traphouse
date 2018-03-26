#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <math.h>
#include "Player.h"


Map::Map():map(sf::Vector2f(1080,720)) {
    map.setFillColor(sf::Color::Red);
    map.setPosition(0,0);
    bottom = map.getPosition().y + map.getSize().y;
    top = map.getPosition().y;
    right = map.getPosition().x + map.getSize().x;
    left = map.getPosition().x;
}

int Map::collisionTest(Player *player) {
    int collision = 0;
    if(player->getPlayer().getPosition().y < top+5){
        collision = 1;
    }
    if(player->getPlayer().getPosition().y >= bottom-70){
        collision = 2;
    }
    if(player->getPlayer().getPosition().x >= right-50){
        collision = 3;
    }
    if(player->getPlayer().getPosition().x <= left+5){
        collision = 4;
    }
    if(player->getPlayer().getPosition().y < top+5 && player->getPlayer().getPosition().x >= right-50){
         collision = 5;
    } if(player->getPlayer().getPosition().y < top+5 && player->getPlayer().getPosition().x <= left+5){
        collision = 6;
    }  if(player->getPlayer().getPosition().y >= bottom-70 && player->getPlayer().getPosition().x >= right-50){
        collision = 7;
    }   if(player->getPlayer().getPosition().y >= bottom-70 && player->getPlayer().getPosition().x <= left+5){
        collision = 8;
    }
    return collision;
}