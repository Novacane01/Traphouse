#pragma once
#include "GameManager.h"
#include "Player.h"

class Map
{
public:
	Map();
	sf::RectangleShape map;
	void collisionTest(Player*);

private:
	sf::Texture txture;
};