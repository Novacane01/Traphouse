#include "SFML\Graphics.hpp"
class Enemy
{
public:
	Enemy();
	void setName(std::string);
    void setHp();
	void setWalkspeed(int);
	std::string getName();
 	int getLevel();
 	int getWalkspeed();
	int getHp();
	int getAttack();
 	sf::Sprite() getEnemy();
 	void Update(double);
	~Enemy();
private:
	int hp = 0;
	double walkspeed = 0;
	int attack = 0;
};