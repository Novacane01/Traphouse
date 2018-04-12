//#include "stdafx.h"
#include "Map.h"
#include <iostream>
#include <math.h>


Map::Map(){
	if (!texture.loadFromFile("Sprites\\Map\\DungeonFloorStone.png")) {
		std::cout << "Could not load from file" << std::endl;
	}
	map.setTexture(texture);
}

void Map::collisionTest(Player *player) {
	if (player->getPlayer().getGlobalBounds().intersects(map.getGlobalBounds())) {
	}
}

void Map::Draw(sf::RenderWindow &window) {
	window.draw(map);
}