#include "GameManager.h"
class Map
{
public:
	Map();
	void Generate();
	~Map();
private:
	sf::RectangleShape *map;
	sf::Texture txture;
};