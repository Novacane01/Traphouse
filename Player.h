#include "SFML\Graphics.hpp"
#include <iostream>
class Player
{
public:
	 Player();
	 void setName(std::string);
	 void setLevel(int);
	 void setHp(int);
	 void setAttack(int);
	 void setWalkspeed(double);

	 void LevelUp();
	 std::string getName();
	 int getLevel();
	 int getWalkspeed();
	 int getHp();
	 int getAttack();
	 sf::Sprite() getPlayer();
	 void Update();
	~Player();

private:
	const std::string name;
	sf::Spirte player;
	sf::Texture texture;
	int level 0;
	int hp = 0;
	int attack = 0;
	double walkspeed = 0;
};