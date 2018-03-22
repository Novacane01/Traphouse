#include "Pickup.h"
#include "SFML/Graphics.hpp"
#include <iostream>
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