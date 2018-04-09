
#include "Map.h"
#include <iostream>
#include <math.h>


Map::Map():map(sf::Vector2f(100,100)) {
    map.setFillColor(sf::Color::Red);
    map.setPosition(100,100);
}

void Map::collisionTest(Player *player) {
	if (player->getPlayer().getGlobalBounds().intersects(map.getGlobalBounds())) {
	}
}