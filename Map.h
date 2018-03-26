#ifndef MAP_H
#define MAP_H
#include "GameManager.h"

class Map
{
public:
	Map();
	sf::RectangleShape map;
	int collisionTest(Player*);

private:
	float bottom, top, right, left;
	sf::Texture txture;
};

#endif