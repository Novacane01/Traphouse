#pragma once
#include "GameManager.h"
#include "Player.h"

class Floor
{
public:
	Floor();
	void Draw(sf::RenderWindow &);

private:
	sf::Sprite floor;
	sf::Texture texture;
};