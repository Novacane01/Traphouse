#pragma once
#include "GameManager.h"
#include "Player.h"

class Floor
{
public:
	Floor();
	void collisionTest(Player*);
	void Draw(sf::RenderWindow &);

private:
	sf::Sprite floor;
	sf::Texture texture;
};