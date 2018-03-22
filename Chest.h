#pragma once

#include "Pickup.h"
#include "GameManager.h"

class Chest
{
public:
	Chest(sf::Texture &);
	std::vector<Pickup> Open();
	~Chest();
	
private:
	sf::Sprite chest;
	sf::Texture texture;
};