#pragma once
#include "GameManager.h"
#include "Player.h"

class Map
{
public:
	Map();
	void collisionTest(Player*);
	void Draw(sf::RenderWindow &);

private:
	sf::Sprite map;
	sf::Texture texture;
};